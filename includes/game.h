#include <stdio.h>
#ifndef GAME_H
#define GAME_H
#define TIMER 30

typedef struct {
    float x;
    float y;
    float vector;
} Obstacle;

void on_keyboard(unsigned char key, int x, int y);
void on_display(void);
void on_reshape(int width, int height);
void on_timer(int value);

void initialize(void);
void detectCollisionWithRoad();
void detecCollisionWihtObstacles(int);

void setLight();
void screen_size();

void drawBall(void);
void drawObstacle(void);
void drawRoad(void);

void initialValues();

void writeScore();
void writeLevel();
void writeLevelUp();
void writeMessage();
#endif
