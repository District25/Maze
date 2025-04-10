#include <QApplication>
#include "gamecontroller.h"
#include "gamefactory.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // 🔥 Création du GameController via la Factory
    GameController* controller = GameFactory::createGameController();

    return app.exec();
}
