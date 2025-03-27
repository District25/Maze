#ifndef OUTPUTVIEW_H
#define OUTPUTVIEW_H

#include <QString>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>

#include "Coord.h"
#include "Observer.h"
#include "maze.h"

class OutputView : public QGraphicsView, public Observer{
    Q_OBJECT
private :
    Maze* model;
    QGraphicsScene *scene;
public:
    explicit OutputView(Maze *maze, QWidget *parent = nullptr);
    void update() override;
    void drawMaze();
};

#endif // OUTPUTVIEW_H
