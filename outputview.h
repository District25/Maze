#ifndef OUTPUTVIEW_H
#define OUTPUTVIEW_H

#include <QString>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>

#include "Coord.h"
#include "Observer.h"
#include "maze.h"
#include "algorithm.h"

class GameController;

class OutputView : public QGraphicsView, public Observer{
    Q_OBJECT
private :
    Maze* model;
    Algorithm* algo;
    QGraphicsScene *scene;
    GameController* controller = nullptr;
public:
    explicit OutputView(Maze *maze, QWidget *parent = nullptr);
    void setAlgorithm(Algorithm* algorithm);
    void update() override;
    void drawMaze();
    void setController(GameController* gc);
};

#endif // OUTPUTVIEW_H
