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
    Coord initRobotPosition;
    Coord exitPosition;
    int rows=0;
    int col=0;
    bool Win = false;
    bool generated = false;
public:
    Maze();
    Maze(int rows, int col);
    // Getter
    Coord getRobotPosition() const;
    Coord getExitPosition() const;
    Coord getInitRobotPosition() const;
    std::vector<std::vector<int>> getGrid();
    int getRows() const;
    int getCol() const;
    bool getGenerated() const;

    // Setter
    void setWin(bool state);
    void setGrid(const std::vector<std::vector<int>>& newGrid);
    void setRobotPosition(Coord pos);
    void setGenerated(bool state);

    Coord placeRobotRandomly() const;
    void moveRobot(Coord next);
    bool isCellFree(int x, int y) const;
    bool hasWon();
    void placeExit(int rows, int cols);
    void generateMaze(int rows, int cols);
    void resetMaze();

    // Implémentations OBLIGATOIRES des méthodes de Subject
    void subscribe(Observer* o) override;
    void notifyObservers() override;
};

#endif // MAZE_H
