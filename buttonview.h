#ifndef BUTTONVIEW_H
#define BUTTONVIEW_H


#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QProgressBar>

class buttonView : public QWidget
{
    Q_OBJECT

public:
    explicit buttonView(QWidget* parent = nullptr);

signals:
    void saveRequested();
    void loadRequested();
    void randMazeRequested();
    void randRobotPosRequested();
    void start_stopSimulRequested();

private:
    QPushButton *saveButton;
    QPushButton *loadButton;
    QPushButton *randomMazeButton;
    QPushButton *randomRobotButton;
    QPushButton *start_stopButton;
    QLineEdit *rows;
    QLineEdit *cols;
    QLabel *win;
    QLabel* statusLabel;
    QLabel* timer;
    QProgressBar* progressBar;

public:
    int getRows() const;
    int getCols() const;
    void showProcessingUI();
    void winProcessingUI();
    void pauseProcessingUI();
    void hideProcessingUI();
    void setTimer(int min, int sec, int cent);
};

#endif // BUTTONVIEW_H
