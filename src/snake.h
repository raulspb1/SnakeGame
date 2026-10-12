#pragma once
#include <QWidget>
#include <QKeyEvent>
#include <QImage>

class Snake : public QWidget {
    Q_OBJECT

public:
    Snake(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;

private:
    void loadImages();
    void initGame();
    void locateApple();
    void move();
    void checkCollision();

    static const int DOT_SIZE = 10;
    static const int ALL_DOTS = 900;
    static const int FIELD_WIDTH = 300;
    static const int FIELD_HEIGHT = 300;
    static const int DELAY = 140;

    int timerId;
    int apple_x;
    int apple_y;
    int dots;

    int x[ALL_DOTS];
    int y[ALL_DOTS];

    // Объекты для хранения честно загруженных картинок по ТЗ
    QImage apple;
    QImage head;
    QImage dot;

    bool leftDirection;
    bool rightDirection;
    bool upDirection;
    bool downDirection;
    bool inGame;
};
