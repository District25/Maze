#include "mainwindow.h"

#include <QApplication>
<<<<<<< HEAD

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
=======
#include "gamecontroller.h"
#include "gamefactory.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // 🔥 Création du GameController via la Factory
    GameController* controller = GameFactory::createGameController();
    //controller->startGame();

    return app.exec();
>>>>>>> 9e7278f (Temporary commit - waiting to transfer updates to version-1.0 branch)
}
