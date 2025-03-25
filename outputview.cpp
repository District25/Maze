#include "outputview.h"
#include <QDebug>


using namespace std;

OutputView::OutputView(Maze *maze, QWidget *parent) : QWidget(parent), model(maze) {}



void OutputView::update()
{
    QWidget::update();
}


void OutputView::displayMessage(QString message)
{

}

void OutputView::paintEvent(QPaintEvent* event) {
    QPainter painter(this);

    int cellSize = 20;  // Taille des cases du labyrinthe

    Coord robotPos = model->getRobotPosition();
    Coord exitPos = model->getExitPosition();

    for (int i = 0; i < model->getRows(); i++) {
        for (int j = 0; j < model->getCol(); j++) {
            QRect cell(j * cellSize, i * cellSize, cellSize, cellSize);

            if (!model->isCellFree(i, j)) {
                painter.setBrush(Qt::black);  // Mur
            } else if (robotPos.x == i && robotPos.y == j) {
                painter.setBrush(Qt::red);    // Robot
            } else if (exitPos.x == i && exitPos.y == j) {
                painter.setBrush(Qt::green);  // Sortie
            } else {
                painter.setBrush(Qt::white);  // Vide
            }

            painter.drawRect(cell);  // Dessine la cellule
        }
    }
}

