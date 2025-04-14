#include "outputview.h"
#include <QDebug>
#include "gamecontroller.h"


using namespace std;

int cellSize = 5; // Changes the size of the cell we see on window

// Constructor and set scene
OutputView::OutputView(Maze *maze, QWidget *parent) : QGraphicsView(parent), model(maze) {
    int width = (model->getCol() + 2) * cellSize;
    int height = (model->getRows() + 2) * cellSize;

    this->setMinimumSize(600, 600);

    scene = new QGraphicsScene(this);
    scene->setSceneRect(-cellSize, -cellSize, width, height);
    scene->setBackgroundBrush(Qt::white);
    this->setScene(scene);
}

void OutputView::setController(GameController *gc)
{
    controller = gc;
}

void OutputView::setAlgorithm(Algorithm *algorithm)
{
    this->algo = algorithm;
}


// Update what the observers see
void OutputView::update() { drawMaze(); }

// Draw the all maze process in a window
void OutputView::drawMaze()
{
    scene->clear();  // Clearing before redraw

    Coord robotPos = model->getRobotPosition();
    Coord exitPos = model->getExitPosition();

    for (int y = 0; y < model->getRows(); y++) {
        for (int x = 0; x < model->getCol(); x++) {
            QRectF cell(x * cellSize, y * cellSize, cellSize, cellSize);
            QGraphicsRectItem *rect = scene->addRect(cell);

            if (!model->isCellFree(x, y)) {
                rect->setBrush(controller->getWallColor());  // Black walls
                rect->setPen(Qt::NoPen);
            } else if (robotPos.x == x && robotPos.y == y)
                rect->setBrush(controller->getRobotColor()); // Red robot
                else if(exitPos.x == x && exitPos.y == y){
                    rect->setBrush(controller->getExitColor()); // Green exit
            } else {
                rect->setBrush(QColor(Qt::white));  // White path
                rect->setPen(QPen(QColor(Qt::white)));
            }
        }
    }
    // Only enter here after robot has found the exit (win mode -> animation)
    if (model->hasWon() && !algo->getOptimalPath().empty() && controller) {
        size_t trailLength = controller->getIndexAnim();

        for (size_t i = 0; i < trailLength && i < algo->getOptimalPath().size(); ++i) {
            Coord p = algo->getOptimalPath()[i];
            QRectF cell(p.x * cellSize, p.y * cellSize, cellSize, cellSize);
            scene->addRect(cell, QPen(Qt::NoPen), QBrush(controller->getAnimationColor()));
        }
    }
    scene->setSceneRect(0, 0, model->getCol() * cellSize, model->getRows() * cellSize);
    this->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}


