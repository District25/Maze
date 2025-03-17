#include "mainwindow.h"
#include <QApplication>

#include "gamefactory.h"

#define CONSOLE_MODE  // Mets en commentaire quand tu veux GUI
//#define GUI_MODE  // Mets en commentaire quand tu veux console

int main(int argc, char *argv[]) {

#ifdef CONSOLE_MODE
    Maze* maze = GameFactory::createMaze();
    InputView* iv = GameFactory::createInputView();
    OutputView* ov = GameFactory::createOutputView(maze);
    Algorithm* algo = GameFactory::createAlgorithm();

    GameController* controller = GameFactory::createGameController(maze, iv, ov, algo);
    controller->startGame();

    return 0;
#endif

#ifdef GUI_MODE
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
#endif
}
