#include "outputview.h"
#include <QDebug>
#include "gamecontroller.h"


using namespace std;

int cellSize = 10; // Changes the size of the cell we see on window

// Constructor and set scene
OutputView::OutputView(Maze *maze, QWidget *parent) : QGraphicsView(parent), model(maze) {
    int width = (model->getCol() + 2) * cellSize;
    int height = (model->getRows() + 2) * cellSize;

    this->setFixedSize(width, height);
    scene = new QGraphicsScene(this);
    scene->setSceneRect(-10, -10, width, height);
    scene->setBackgroundBrush(Qt::white);
    this->setScene(scene);
}

void OutputView::setAlgorithm(Algorithm *algorithm)
{
    this->algo = algorithm;
}


// Update what the observers see
void OutputView::update()
{
    drawMaze();
}

// Draw the all maze process in a window
void OutputView::drawMaze()
{
    scene->clear();  // Nettoyage avant redessin

    Coord robotPos = model->getRobotPosition();
    Coord exitPos = model->getExitPosition();

    for (int y = 0; y < model->getRows(); y++) {
        for (int x = 0; x < model->getCol(); x++) {
            QRectF cell(x * cellSize, y * cellSize, cellSize, cellSize);
            QGraphicsRectItem *rect = scene->addRect(cell);

            if (!model->isCellFree(x, y)) {
                rect->setBrush(QColor(Qt::black));  // mur foncé
                rect->setPen(Qt::NoPen);
            } else if (robotPos.x == x && robotPos.y == y)
                rect->setBrush(Qt::red);
                else if(exitPos.x == x && exitPos.y == y){
                    rect->setBrush(Qt::green);
            } else {
                rect->setBrush(QColor(Qt::white));  // couloir clair
                rect->setPen(QPen(QColor(Qt::white)));       // contour léger
            }
        }
    }
    if (model->hasWon() && !algo->getOptimalPath().empty() && controller) {
        size_t trailLength = controller->getIndexAnim();

        for (size_t i = 0; i < trailLength && i < algo->getOptimalPath().size(); ++i) {
            Coord p = algo->getOptimalPath()[i];
            QRectF cell(p.x * cellSize, p.y * cellSize, cellSize, cellSize);
            QGraphicsRectItem *rect = scene->addRect(cell);
            if(!(algo->getOptimalPath()[i] == model->getInitRobotPosition())){
                rect->setBrush(QColor(Qt::cyan));
                rect->setPen(QPen(QColor(Qt::cyan)));
            }
        }
    }


}

void OutputView::setController(GameController *gc)
{
    controller = gc;
}

