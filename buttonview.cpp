#include "buttonview.h"


buttonView::buttonView(QWidget *parent) : QWidget(parent)
{
    saveButton = new QPushButton("Save maze", this);
    loadButton = new QPushButton("Load maze", this);
    pauseButton = new QPushButton("Pause", this);
    randomMazeButton = new QPushButton("Generate random maze", this);
    randomRobotButton = new QPushButton("Change robot position", this);
    startButton = new QPushButton("Start", this);

    win = new QLabel();

    saveButton->setGeometry(10, 10, 100, 30);
    loadButton->setGeometry(10, 50, 100, 30);
    pauseButton->setGeometry(10, 90, 100, 30);
    randomMazeButton->setGeometry(10, 130, 200, 30);
    randomRobotButton->setGeometry(10, 170, 200, 30);
    startButton->setGeometry(10, 210, 100, 30);
    win->setGeometry(10, 250, 200, 30);

    connect(saveButton, &QPushButton::clicked, this, &buttonView::saveRequested);
    connect(loadButton, &QPushButton::clicked, this, &buttonView::loadRequested);
    connect(pauseButton, &QPushButton::clicked, this, &buttonView::pauseRequested);
    connect(randomMazeButton, &QPushButton::clicked, this, &buttonView::randMazeRequested);
    connect(randomRobotButton, &QPushButton::clicked, this, &buttonView::randRobotPosRequested);
    connect(startButton, &QPushButton::clicked, this, &buttonView::startSimulRequested);
}
