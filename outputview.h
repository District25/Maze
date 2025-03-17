#ifndef OUTPUTVIEW_H
#define OUTPUTVIEW_H

#include "Observer.h"
#include "Maze.h"
#include "Coord.h"

#include <QString>

class OutputView : public Observer
{
private :
    Maze* model;
public:
    OutputView(Maze* maze);
    void update() override;
    void displayGamefield();
    void displayRobot(Coord pos);
    void displayMessage(QString message);
};

#endif // OUTPUTVIEW_H
