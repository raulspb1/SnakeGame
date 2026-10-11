#include "snake.h"
#include <QPainter>
#include <QTime>

Snake::Snake(QWidget *parent) : QWidget(parent) {
    // Настраиваем фон и размеры окна
    setStyleSheet("background-color:black;");
    leftDirection = false;
    rightDirection = true; // Изначально змейка ползет вправо
    upDirection = false;
    downDirection = false;
    inGame = true;

    resize(FIELD_WIDTH, FIELD_HEIGHT);
    loadImages();
    initGame();
}

void Snake::loadImages() {
    // Метод из условий к практической работе. Инициализируем генератор случайных чисел
    // для будущего размещения яблок
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
}

void Snake::initGame() {
    dots = 3; // Изначальная длина змейки — 3 сегмента

    // Задаем стартовые координаты для тела змейки
    for (int i = 0; i < dots; i++) {
        x[i] = 50 - i * DOT_SIZE;
        y[i] = 50;
    }

    locateApple(); // Спавним первое яблоко
    timerId = startTimer(DELAY); // Запускаем игровой цикл таймера
}

void Snake::locateApple() {
    // Находим случайную ячейку на сетке поля
    int r = qrand() % (FIELD_WIDTH / DOT_SIZE);
    apple_x = r * DOT_SIZE;

    r = qrand() % (FIELD_HEIGHT / DOT_SIZE);
    apple_y = r * DOT_SIZE;
}

void Snake::timerEvent(QTimerEvent *event) {
    Q_UNUSED(event);

    if (inGame) {
        // Если змейка наткнулась на яблоко
        if ((x[0] == apple_x) && (y[0] == apple_y)) {
            dots++; // Увеличиваем длину
            locateApple(); // Создаем новое яблоко
        }
        checkCollision();
        move();
    }

    repaint(); // Принудительно перерисовываем экран
}

void Snake::move() {
    // Перемещаем сегменты тела друг за другом
    for (int i = dots; i > 0; i--) {
        x[i] = x[i - 1];
        y[i] = y[i - 1];
    }

    // Смещаем голову в зависимости от направления
    if (leftDirection)  x[0] -= DOT_SIZE;
    if (rightDirection) x[0] += DOT_SIZE;
    if (upDirection)    y[0] -= DOT_SIZE;
    if (downDirection)  y[0] += DOT_SIZE;
}

void Snake::checkCollision() {
    // Проверяем столкновение с собственным телом
    for (int i = dots; i > 4; i--) {
        if ((x[0] == x[i]) && (y[0] == y[i])) {
            inGame = false;
        }
    }

    // Проверяем выход за границы игрового поля
    if (y[0] >= FIELD_HEIGHT) inGame = false;
    if (y[0] < 0) inGame = false;
    if (x[0] >= FIELD_WIDTH)  inGame = false;
    if (x[0] < 0) inGame = false;

    if (!inGame) {
        killTimer(timerId); // Останавливаем таймер при проигрыше
    }
}

void Snake::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter qp(this);

    if (inGame) {
        // Рисуем красное яблоко размером 10x10
        qp.setBrush(Qt::red);
        qp.drawEllipse(apple_x, apple_y, DOT_SIZE, DOT_SIZE);

        // Рисуем змейку
        for (int i = 0; i < dots; i++) {
            if (i == 0) {
                qp.setBrush(Qt::yellow); // Голова желтая
                qp.drawRect(x[i], y[i], DOT_SIZE, DOT_SIZE);
            } else {
                qp.setBrush(Qt::green);  // Тело зеленое
                qp.drawRect(x[i], y[i], DOT_SIZE, DOT_SIZE);
            }
        }
    } else {
        // Окно Game Over в центре поля
        qp.setPen(Qt::white);
        setFont(QFont("Courier", 15, QFont::Bold));
        qp.drawText(rect(), Qt::AlignCenter, "Game Over");
    }
}

void Snake::keyPressEvent(QKeyEvent *event) {
    int key = event->key();

    // Меняем направление, запрещая разворот на 180 градусов
    if ((key == Qt::Key_Left) && (!rightDirection)) {
        leftDirection = true; upDirection = false; downDirection = false;
    }
    if ((key == Qt::Key_Right) && (!leftDirection)) {
        rightDirection = true; upDirection = false; downDirection = false;
    }
    if ((key == Qt::Key_Up) && (!downDirection)) {
        upDirection = true; rightDirection = false; leftDirection = false;
    }
    if ((key == Qt::Key_Down) && (!upDirection)) {
        downDirection = true; rightDirection = false; leftDirection = false;
    }
}
