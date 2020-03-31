#include <stdio.h>
#ifndef GAME_H
#define GAME_H


void on_keyboard(unsigned char key, int x, int y);
void on_display(void);
void on_reshape(int width, int height);

void initialize(void);

void setLight();

void drawBall(void);
void drawRoad(void);

#endif