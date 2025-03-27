#include "outputview.h"
#include <QDebug>


using namespace std;

int cellSize = 20;

OutputView::OutputView(Maze *maze, QWidget *parent) : QGraphicsView(parent), model(maze) {
    int width = (model->getCol() + 2) * cellSize;
    int height = (model->getRows() + 2) * cellSize;

    this->setFixedSize(width, height);
    scene = new QGraphicsScene(this);
    scene->setSceneRect(-10, -10, width, height);
    scene->setBackgroundBrush(Qt::white);
    this->setScene(scene);
}



void OutputView::update()
{
    drawMaze();
}

void OutputView::drawMaze()
{
    scene->clear();  // Nettoyage avant redessin

    Coord robotPos = model->getRobotPosition();
    Coord exitPos = model->getExitPosition();

    for (int y = 0; y < model->getRows(); y++) {
        for (int x = 0; x < model->getCol(); x++) {
            QRectF cell(x * cellSize, y * cellSize, cellSize, cellSize);
            QGraphicsRectItem *rect = scene->addRect(cell);

            if (!model->isCellFree(y, x)) {
                rect->setBrush(QColor("#222222"));  // mur foncé
                rect->setPen(Qt::NoPen);
            } else if (robotPos.x == x && robotPos.y == y) {
                rect->setBrush(Qt::red);
            } else if (exitPos.x == x && exitPos.y == y) {
                rect->setBrush(Qt::green);
            } else {
                rect->setBrush(QColor("#eeeeee"));  // couloir clair
                rect->setPen(QPen(QColor("#eeeeee")));       // contour léger
            }
        }
    }
}

