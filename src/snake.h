#pragma once
#include <QWidget>
#include <QKeyEvent>

class Snake : public QWidget {
    Q_OBJECT

public:
    Snake(QWidget *parent = nullptr);

protected:
    // Системные события Qt для отрисовки графики, нажатия клавиш и тиков таймера
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;

private:
    // Обязательные методы из условий к практической работе
    void loadImages();
    void initGame();
    void locateApple();
    void move();
    void checkCollision();

    // Константы игрового поля (размер ячейки 10px, поле 300x300px)
    static const int DOT_SIZE = 10;
    static const int ALL_DOTS = 900; // Максимальное количество сегментов (30 * 30)
    static const int FIELD_WIDTH = 300;
    static const int FIELD_HEIGHT = 300;
    static const int DELAY = 140;    // Скорость игры (интервал таймера в мс)

    // Игровые переменные
    int timerId;
    int apple_x;
    int apple_y;
    int dots; // Текущая длина змейки

    // Массивы для хранения координат всех сегментов змейки
    int x[ALL_DOTS];
    int y[ALL_DOTS];

    // Направления движения
    bool leftDirection;
    bool rightDirection;
    bool upDirection;
    bool downDirection;
    bool inGame;
};
