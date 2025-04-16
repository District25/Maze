#include "outputview.h"
#include <QDebug>
#include "gamecontroller.h"
#include <set>

using namespace std;

int cellSize = 6; // Plus clean que 5, évite le flou sur gros labyrinthes

OutputView::OutputView(Maze *maze, QWidget *parent) : QGraphicsView(parent), model(maze)
{
    this->setMinimumSize(600, 600);

    scene = new QGraphicsScene(this);
    this->setScene(scene);

    // Optimisation affichage
    this->setRenderHint(QPainter::Antialiasing, false);
    this->setRenderHint(QPainter::TextAntialiasing, false);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    this->setTransformationAnchor(QGraphicsView::AnchorViewCenter);
    this->setResizeAnchor(QGraphicsView::AnchorViewCenter);
}

void OutputView::setController(GameController *gc) {
    controller = gc;
}

void OutputView::setAlgorithm(Algorithm *algorithm) {
    this->algo = algorithm;
}

void OutputView::initGrid()
{
    scene->clear();
    visitedTrail.clear();
    rectGrid.clear();

    int rows = model->getRows();
    int cols = model->getCol();
    rectGrid.resize(rows, std::vector<QGraphicsRectItem*>(cols, nullptr));

    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            QRectF cell(x * cellSize, y * cellSize, cellSize, cellSize);
            auto* rect = scene->addRect(cell);
            rect->setPen(Qt::NoPen);
            rect->setBrush(Qt::white);
            rectGrid[y][x] = rect;
        }
    }

    // Adapter la taille de la scène à la grille
    scene->setSceneRect(0, 0, cols * cellSize, rows * cellSize);
    this->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

void OutputView::updateAllWalls()
{
    for (int y = 0; y < model->getRows(); ++y) {
        for (int x = 0; x < model->getCol(); ++x) {
            if (!model->isCellFree(x, y)) {
                updateCell(x, y); // Affiche les murs uniquement
            }
        }
    }
}

void OutputView::updateCell(int x, int y)
{
    if (y >= rectGrid.size() || x >= rectGrid[y].size()) return;

    QGraphicsRectItem* rect = rectGrid[y][x];
    if (!rect) return;

    Coord robotPos = model->getRobotPosition();
    Coord exitPos = model->getExitPosition();

    // Le robot doit être affiché EN PRIORITÉ
    if (robotPos.x == x && robotPos.y == y) {
        rect->setBrush(controller->getRobotColor());
    }
    else if (!model->isCellFree(x, y)) {
        rect->setBrush(controller->getWallColor());
    }
    else if (exitPos.x == x && exitPos.y == y) {
        rect->setBrush(controller->getExitColor());
    }
    else if (visitedTrail.find(Coord(x, y)) != visitedTrail.end()) {
        rect->setBrush(controller->getAnimationColor());
    }
    else {
        rect->setBrush(Qt::white);
    }
}


void OutputView::update() {
    drawMaze();
}

void OutputView::drawMaze()
{
    if (rectGrid.empty()) return;

    Coord robotPos = model->getRobotPosition();

    // Animation : trace le chemin au fur et à mesure
    if (model->hasWon() && !algo->getOptimalPath().empty()) {
        size_t i = controller->getIndexAnim();
        if (i < algo->getOptimalPath().size()) {
            Coord p = algo->getOptimalPath()[i];
            visitedTrail.insert(p);
        }

        // Colorier tout le trail d'abord
        for (const Coord& c : visitedTrail) {
            if (c.y < rectGrid.size() && c.x < rectGrid[c.y].size())
                rectGrid[c.y][c.x]->setBrush(controller->getAnimationColor());
        }
    }

    // Mettre à jour la case du robot EN DERNIER pour qu'elle soit par-dessus le trail
    updateCell(robotPos.x, robotPos.y);
}

