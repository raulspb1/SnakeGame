#include "snake.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Snake game;
    game.setWindowTitle("Snake");
    game.show();

    return app.exec();
}
