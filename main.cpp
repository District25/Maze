#include <QApplication>
#include "gamecontroller.h"
#include "gamefactory.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Creation of controller
    GameController* controller = GameFactory::createGameController();

    return app.exec();
}
