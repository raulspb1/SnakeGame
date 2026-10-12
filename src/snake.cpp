#include "snake.h"
#include <QPainter>
#include <QTime>
#include <QImage>

Snake::Snake(QWidget *parent) : QWidget(parent) {
    setStyleSheet("background-color:black;");
    leftDirection = false;
    rightDirection = true;
    upDirection = false;
    downDirection = false;
    inGame = true;

    resize(FIELD_WIDTH, FIELD_HEIGHT);
    loadImages();
    initGame();
}

void Snake::loadImages() {
    // Автоматически создаем картинки размером 10x10 пикселей, чтобы не качать их из интернета
    QImage appleImg(DOT_SIZE, DOT_SIZE, QImage::Format_ARGB32);
    appleImg.fill(Qt::transparent);
    QPainter p1(&appleImg);
    p1.setBrush(Qt::red);
    p1.setPen(Qt::NoPen);
    p1.drawEllipse(0, 0, DOT_SIZE, DOT_SIZE);
    p1.end();
    appleImg.save("apple.png");

    QImage headImg(DOT_SIZE, DOT_SIZE, QImage::Format_ARGB32);
    headImg.fill(Qt::transparent);
    QPainter p2(&headImg);
    p2.setBrush(Qt::yellow);
    p2.setPen(Qt::NoPen);
    p2.drawRect(0, 0, DOT_SIZE, DOT_SIZE);
    p2.end();
    headImg.save("head.png");

    QImage dotImg(DOT_SIZE, DOT_SIZE, QImage::Format_ARGB32);
    dotImg.fill(Qt::transparent);
    QPainter p3(&dotImg);
    p3.setBrush(Qt::green);
    p3.setPen(Qt::NoPen);
    p3.drawRect(0, 0, DOT_SIZE, DOT_SIZE);
    p3.end();
    dotImg.save("dot.png");

    // ЧЕСТНАЯ ЗАГРУЗКА ИЗОБРАЖЕНИЙ ПО ТРЕБОВАНИЮ КУРАТОРА
    apple.load("apple.png");
    head.load("head.png");
    dot.load("dot.png");

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
}

void Snake::initGame() {
    dots = 3;

    for (int i = 0; i < dots; i++) {
        x[i] = 50 - i * DOT_SIZE;
        y[i] = 50;
    }

    locateApple();
    timerId = startTimer(DELAY);
}

void Snake::locateApple() {
    int r = qrand() % (FIELD_WIDTH / DOT_SIZE);
    apple_x = r * DOT_SIZE;

    r = qrand() % (FIELD_HEIGHT / DOT_SIZE);
    apple_y = r * DOT_SIZE;
}

void Snake::timerEvent(QTimerEvent *event) {
    Q_UNUSED(event);

    if (inGame) {
        if ((x[0] == apple_x) && (y[0] == apple_y)) {
            dots++;
            locateApple();
        }
        checkCollision();
        move();
    }

    repaint();
}

void Snake::move() {
    for (int i = dots; i > 0; i--) {
        x[i] = x[i - 1];
        y[i] = y[i - 1];
    }

    if (leftDirection)  x[0] -= DOT_SIZE;
    if (rightDirection) x[0] += DOT_SIZE;
    if (upDirection)    y[0] -= DOT_SIZE;
    if (downDirection)  y[0] += DOT_SIZE;
}

void Snake::checkCollision() {
    // ИСПРАВЛЕНО ПО ЗАМЕЧАНИЮ КУРАТОРА: строгая проверка сегментов тела до dots - 1
    for (int i = dots - 1; i > 4; i--) {
        if ((x[0] == x[i]) && (y[0] == y[i])) {
            inGame = false;
        }
    }

    if (y[0] >= FIELD_HEIGHT) inGame = false;
    if (y[0] < 0) inGame = false;
    if (x[0] >= FIELD_WIDTH)  inGame = false;
    if (x[0] < 0) inGame = false;

    if (!inGame) {
        killTimer(timerId);
    }
}

void Snake::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter qp(this);

    if (inGame) {
        // РИСОВАНИЕ С ПОМОЩЬЮ ЗАГРУЖЕННЫХ ИЗОБРАЖЕНИЙ ПО ТЗ
        qp.drawImage(apple_x, apple_y, apple);

        for (int i = 0; i < dots; i++) {
            if (i == 0) {
                qp.drawImage(x[i], y[i], head);
            } else {
                qp.drawImage(x[i], y[i], dot);
            }
        }
    } else {
        qp.setPen(Qt::white);
        setFont(QFont("Courier", 15, QFont::Bold));
        qp.drawText(rect(), Qt::AlignCenter, "Game Over");
    }
}

void Snake::keyPressEvent(QKeyEvent *event) {
    int key = event->key();

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
