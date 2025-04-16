#ifndef OUTPUTVIEW_H
#define OUTPUTVIEW_H

#include <QString>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <set>

#include "Observer.h"
#include "maze.h"
#include "algorithm.h"
#include "Coord.h"

class GameController;

class OutputView : public QGraphicsView, public Observer{
    Q_OBJECT
private :
    Maze* model;
    Algorithm* algo;
    QGraphicsScene *scene;
    GameController* controller = nullptr;

    std::vector<std::vector<QGraphicsRectItem*>> rectGrid;
    std::set<Coord> visitedTrail; // Contient les cases déjà coloriées


public:
    void initGrid();
    void updateCell(int x, int y);
    void updateAllWalls();
    explicit OutputView(Maze *maze, QWidget *parent = nullptr);
    void setAlgorithm(Algorithm* algorithm);
    void update() override;
    void drawMaze();
    void setController(GameController* gc);
};

#endif // OUTPUTVIEW_H
