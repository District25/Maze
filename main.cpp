#include <QApplication>
#include "gamecontroller.h"
#include "gamefactory.h"
#include "inputview.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // 🔥 Création du GameController via la Factory
    GameController* controller = GameFactory::createGameController();
    controller->startGame();

    return app.exec();
}
