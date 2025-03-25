#ifndef OUTPUTVIEW_H
#define OUTPUTVIEW_H

#include <QString>
#include <QWidget>
#include <QPainter>

#include "Coord.h"
#include "Observer.h"
#include "maze.h"

class OutputView : public QWidget, public Observer{
    Q_OBJECT
private :
    Maze* model;
public:
    explicit OutputView(Maze *maze, QWidget *parent = nullptr);
    void update() override;
    void displayMessage(QString message);
protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // OUTPUTVIEW_H
