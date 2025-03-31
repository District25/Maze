#ifndef BUTTONVIEW_H
#define BUTTONVIEW_H


#include <QWidget>
#include <QPushButton>
#include <QLabel>

class buttonView : public QWidget
{
    Q_OBJECT

public:
    explicit buttonView(QWidget* parent = nullptr);

signals:
    void saveRequested();
    void loadRequested();
    void pauseRequested();
    void randMazeRequested();
    void randRobotPosRequested();
    void startSimulRequested();

private:
    QPushButton *saveButton;
    QPushButton *loadButton;
    QPushButton *pauseButton;
    QPushButton *randomMazeButton;
    QPushButton *randomRobotButton;
    QPushButton *startButton;
    QLabel *win;
};

#endif // BUTTONVIEW_H
