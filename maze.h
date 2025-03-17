#ifndef MAZE_H
#define MAZE_H

#include "Subject.h"
#include "Coord.h"
#include <vector>

class Maze : public Subject
{
private:
    std::vector<std::vector<int>> grid;
    Coord robotPosition;
    Coord exitPosition;
public:
    Maze();
    Maze(int rows, int cols);

    Coord getRobotPosition() const;
    Coord getExitPosition() const;
    void moveRobot(Coord next);
    bool isCellFree(int x, int y) const;

    // Implémentations OBLIGATOIRES des méthodes de Subject
    void subscribe(Observer* o) override;
    void notifyObservers() override;
};

#endif // MAZE_H
