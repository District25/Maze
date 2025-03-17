#include "outputview.h"
#include <iostream>

using namespace std;

OutputView::OutputView(Maze* maze) {
    model = maze;
    model->subscribe(this);
}

void OutputView::update()
{
    displayGamefield();
    //displayRobot(model->getRobotPosition());
}

void OutputView::displayGamefield()
{
    Coord robotPos = model->getRobotPosition();
    Coord exitPos = model->getExitPosition();

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (robotPos.x == i && robotPos.y == j) {
                cout << "R ";  // Robot
            } else if (exitPos.x == i && exitPos.y == j) {
                cout << "S ";  // Sortie
            } else if (!(model->isCellFree(i, j))) {
                cout << "# ";  // Mur
            } else {
                cout << "  ";  // Vide
            }
        }
        cout << endl;  // Important pour aller à la ligne
    }
}

void OutputView::displayRobot(Coord pos)
{
    /* Inutile en v0*/
}

void OutputView::displayMessage(QString message)
{

}
