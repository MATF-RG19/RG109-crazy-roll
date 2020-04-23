#include <stdio.h>
#ifndef GAME_H
#define GAME_H
#define TIMER 30


void on_keyboard(unsigned char key, int x, int y);
void on_display(void);
void on_reshape(int width, int height);
void on_timer(int value);

void initialize(void);
void detectCollisionWithRoad();

void setLight();

void drawBall(void);
void drawRoad(void);

#endif