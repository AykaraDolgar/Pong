#include <stdio.h>

void clearScreen();

int game(int, int);
void drawGame(int, int, int, int, int, int, int, int);
int racketPosition(int, int, int, int, int);
int ballPosition(int, int, int, int);
int edgePosition(int, int, int, int);
int centerPosition(int, int, int);
int ballMove_X(int, int, int, int, int);
int ballMove_Y(int, int, int, int, int, int);
int newVector_X(int, int, int, int, int, int);
int newVector_Y(int, int, int);
int newR_StartY1(char, int, int);
int newR_StartY2(char, int, int);
int score1(int, int, int, int);
int score2(int, int, int, int, int);

int main() {
    int width = 80, height = 25;                          //поле
    int ballStartX = width / 2, ballStartY = height / 2;  //координаты начальнонго положения
    int ballX = ballStartX, ballY = ballStartY, p1 = 0, p2 = 0;
    int vectorX = -1, vectorY = 1, rStartY1 = 12, rStartY2 = 12;

while (1) {
        char key;
        drawGame(width, height, ballX, ballY, rStartY1, rStartY2, p1, p2);
        vectorX = newVector_X(ballX, width, vectorX, ballY, rStartY1, rStartY2);
        vectorY = newVector_Y(ballY, height, vectorY);
        ballX += vectorX;
        ballY += vectorY;
        if (ballX < 2) {
            p2 += 1;
            ballX = ballStartX;
            ballY = ballStartY;  // возвращает начальное положение мяча по центру
        }
        if (ballX > width - 1) {  // при вылете мяча, засчитываются очки первому игроку
            p1 += 1;
            ballX = ballStartX;
            ballY = ballStartY;  // возвращает начальное положение мяча по центру
        }
        key = getchar();

        if (p1 == 21) {
            printf("Победил первый игрок\n");
        }
        if (p2 == 21) {
            printf("Победил второй игрок\n");
        }
        if (p1 == 21 || p2 == 21 || key == ' ') {
            return 1;
        }
        rStartY1 = newR_StartY1(key, rStartY1, height);
        rStartY2 = newR_StartY2(key, rStartY2, height);
        clearScreen();
    }
}

void drawGame(int w, int h, int ballX, int ballY, int rY1, int rY2, int p1, int p2) {
    int screenX = 33, screenY = 3;  //координаты вывода счета
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            if (racketPosition(x, y, rY1, rY2, w)) {
                printf("|");
            } else if (ballPosition(x, y, ballX, ballY)) {
                printf("o");
            } else if (edgePosition(x, y, w, h)) {
                printf("|");
            } else if (centerPosition(x, y, w)) {
                printf("|");
            } else if (score1(x, screenX, screenY, y)) {
                printf("%02d", p1);
            } else if (score2(x, screenX, screenY, y, w)) {
                printf("%02d", p2);
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

int racketPosition(int x, int y, int rStartY1, int rStartY2, int w) {  // положение ракеток
    int racketX1 = 1, racketX2 = w - 2;
    int done = 0;
    if (x == racketX1) {
        if (y == rStartY1 - 1 || y == rStartY1 || y == rStartY1 + 1) {
            done = 1;
        }
    }

    else if (x == racketX2) {
        if (y == rStartY2 - 1 || y == rStartY2 || y == rStartY2 + 1) {
            done = 1;
        }
    }

    return done;
}

int ballPosition(int x, int y, int ballX, int ballY) {  // положение мяча
    int done = 0;
    if (x == ballX && y == ballY) {
        done = 1;
    }

    return done;
}

int edgePosition(int x, int y, int w, int h) {  // грани
    int done = 0;

    if (y == 0 && x != 0 && x != w) {
        done = 1;
    } else if (y == h - 1 && x != 0 && x != w - 1) {
        done = 1;
    } else if (x == 0 && y != 0 && y != h) {
        done = 1;
    } else if (x == w - 1 && x != 0 && y != h - 1 && y != 3) {
        done = 1;
    } else if (x == w / 2 && y != 3) {
        done = 1;
    } else if (x == w - 3 && y == 3) {
        done = 1;
    }

    return done;
}

int centerPosition(int x, int y, int w) {  // середина
    int done = 0;

    if ((x == w / 2 - 1 && y == 3)) {
        done = 1;
    }
    return done;
}

int score1(int x, int screenX, int screenY, int y) {  // очки первого
    int done = 0;
    if (x == screenX && y == screenY) {
        done = 1;
    }
    return done;
}

int score2(int x, int screenX, int screenY, int y, int w) {  // очки второго
    int done = 0;
    if (x == (w - screenX - 2) && y == screenY) {
        done = 1;
    }
    return done;
}

int newVector_X(int ballX, int w, int vX, int ballY, int rSY1, int rSY2) {
    int racketX1 = 1, racketX2 = w;
    if (ballX == racketX1 + 1) {
        if (ballY == rSY1 - 1 || ballY == rSY1 || ballY == rSY1 + 1) {
            vX = -vX;
        }
    }

    if (ballX == racketX2 - 1) {
        if (ballY == rSY2 - 1 || ballY == rSY2 || ballY == rSY2 + 1) {
            vX = -vX;
        }
    }

    return vX;
}

int newVector_Y(int ballY, int h, int vectorY) {
    if (ballY == 1 || ballY == h - 2) {
        vectorY = -vectorY;
    }

    return vectorY;
}

int newR_StartY1(char key, int rStartY1, int h) {
    if (key == 'a') {
        if (rStartY1 - 2 != 0) {
            rStartY1--;
        }
    }
    if (key == 'z') {
        if (rStartY1 + 2 != h - 1) rStartY1++;
    }
    return rStartY1;
}

int newR_StartY2(char key, int rStartY2, int h) {
    if (key == 'k') {
        if (rStartY2 - 2 != 0) {
            rStartY2--;
        }
    }
    if (key == 'm') {
        if (rStartY2 + 2 != h - 1) {
            rStartY2++;
        }
    }
    return rStartY2;
}

void clearScreen() { printf("\33[0d\33[2J"); }
