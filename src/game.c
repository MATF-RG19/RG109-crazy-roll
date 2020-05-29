#include "../includes/game.h"
#include <math.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

float animationPar = 0;
float translationPar = 0;
float linesPar = 0;
int animation_ongoing = 0;
int timer_id = 0;
int level = 1;
float score = -0.2;
float speedPar = 0.05;
float obstaclesPar = 0.01;
int gameOver = 0;
int fullscreen = 0;

Obstacle obstacles[10];

void initialValues() {
    srand(time(NULL));
    int i;
    for(i = 0; i<10;i++)
    {
        obstacles[i].y = 25;
        obstacles[i].x = rand() % 5 - 2.5 ;
        obstacles[i].vector=obstaclesPar *(rand()%10 -5);
        if(obstacles[i].vector == 0)
            obstacles[i].vector = obstaclesPar*3;
    }
}



void on_keyboard(unsigned char key, int x, int y)
{
    (void)x;
    (void)y;
    switch (key) {
        case 27:
            exit(0);
        case 'f':
        case 'F':
            screen_size();
            break;
            break;
        case ' ': 
            if(!animation_ongoing & !gameOver) {
                animation_ongoing = 1;
                glutTimerFunc(TIMER, on_timer, timer_id);
            }
            else
                animation_ongoing = 0;
            break;
        case 'a':
            translationPar += 0.1;
            break;
        case 'd':
            translationPar -= 0.1;
            break;
    }
}

void setLight()
{
    GLfloat lightPosition[] = { -5, 1, 7, 0 };
    GLfloat lightAmbient[] = { 0.0, 0.0, 0.0, 1 };
    GLfloat lightDiffuse[] = { 0.6, 0.6, 0.6, 1 };
    GLfloat lightSpecular[] = { 0.3, 0.3, 0.3, 1 };

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
}

void on_reshape(int width, int height) 
{   
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float) width / height, 1, 40);
}

void on_display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0, -4, 3, 0, 0, 0, 0, 1, 0);    /*GameMode*/
    //gluLookAt(0, 0, 35, 0, 5,0, 0, 0, 1);     /*DevMode*/


    setLight();

    drawRoad();
    drawObstacle();
    drawBall();
    writeScore();
    writeLevel();
    glutSwapBuffers();
}

void initialize(void)
{
    srand(time(NULL));
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowSize(1000, 1000);

    glutInitWindowPosition(0 , 0);
    glutCreateWindow("Crazy roll");
    
    glutKeyboardFunc(on_keyboard);
    
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);
    
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    
}

void drawBall(void)
{   

    GLfloat ambientCoeffs[] = { 0.2, 0.02, 0.02, 1 };
    GLfloat diffuseCoeffs[] = { 0.7, 0.07, 0.07, 1 };
    GLfloat specularCoeffs[] = { 0.7, 0.6, 0.6, 1 };


    GLfloat shininess = 20;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambientCoeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseCoeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specularCoeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    glPushMatrix();
        glTranslatef(0, -1, 0.3);
        detectCollisionWithRoad();
        glTranslatef(-translationPar, 0, 0);
        glRotatef(-animationPar, 1, 0, 0);
        glutSolidSphere(0.3, 20, 20);
    glPopMatrix();
}

void detectCollisionWithRoad() {
    if(translationPar < -2.9)
        translationPar = -2.9;
    else if(translationPar > 2.9)
        translationPar = 2.9;
}

void drawRoad(void) {

    GLfloat ambientCoeffs[] = { 0.3, 0.3, 0.3, 1 };
    GLfloat diffuseCoeffs[] = { 0.45, 0.45, 0.45, 1 };
    GLfloat specularCoeffs[] = { 0.55, 0.55, 0.55, 1 };
    GLfloat shininess = 10;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambientCoeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseCoeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specularCoeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    glPushMatrix();
    glBegin(GL_POLYGON);
        glVertex3f(3, -3, -0.01);
        glVertex3f(-3, -3, -0.01);
        glVertex3f(-3, 25, -0.01);
        glVertex3f(3, 25, -0.01);
    glEnd();
    glPopMatrix();
    
    glDisable(GL_LIGHTING);
    
    glColor3f(1, 1, 1);
    

    int i;
    for(i = 0; i < 15; i++) {
        double x;
        x = -3 + i*2;
        glPushMatrix();
        glTranslatef(0, -linesPar, 0);
        glBegin(GL_POLYGON);
            glVertex3f(0.1,x, 0);
            glVertex3f(-0.1,x, 0);
            glVertex3f(-0.1,x+1.5, 0);
            glVertex3f(0.1,x+1.5, 0);
        glEnd();
        glPopMatrix();
    }
    glEnable(GL_LIGHTING);
}

void on_timer(int value) {
    if(value != timer_id)
        return;
    
    animationPar += 30;
    if(animationPar >= 2880)
        animationPar = 0;
    linesPar += speedPar;
    if(linesPar >= 2)
        linesPar = 0;
    glutPostRedisplay();
    
    if(animation_ongoing)
        glutTimerFunc(TIMER, on_timer, timer_id);
}

void drawObstacle(void) {
    
    GLfloat ambientCoeffs[] = { 0.2, 0.2, 0.2, 1 };
    GLfloat diffuseCoeffs[] = { 0, 0.7, 0.7, 1 };
    GLfloat specularCoeffs[] = { 0, 1, 1, 1 };
    GLfloat shininess = 10;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambientCoeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseCoeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specularCoeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    if(score>1152 & score<1158){
        level=10;
        writeLevelUp();
    }
    else if(score>973 & score<979){
        level=9;
        writeLevelUp();
    }
    else if(score>795 & score<801){
        level=8;
        writeLevelUp();
    }
    else if(score>659 & score<665){
        level=7;
        writeLevelUp();
    }
    else if(score>505 & score<511){
        level=6;
        writeLevelUp();
    }
    else if(score>379 & score<385){
        level=5;
        writeLevelUp();
    }
    else if(score>254 & score<260){
        level=4;
        writeLevelUp();
    }
    else if(score>131 & score<137){
        level=3;
        writeLevelUp();
    }
    else if(score>65 & score<71){
        level=2;
        writeLevelUp();
    }

    int i;
    for(i = 0; i < level; i++) {
        obstacles[i].x += obstacles[i].vector;
        if(obstacles[i].x > 3 || obstacles[i].x < -3) 
            obstacles[i].vector *= -1;

        obstacles[i].y -= speedPar;

        if(obstacles[i].y < -3) {
            obstacles[i].y = 25;
            obstacles[i].vector=obstaclesPar *(rand()%10 -5);
            if(obstacles[i].vector == 0)
                obstacles[i].vector = obstaclesPar*3;
        }
        if(obstacles[i].y <= 0 && obstacles[i].y >= -2) 
            detecCollisionWihtObstacles(i);
            
        
        glPushMatrix();
            glTranslatef(obstacles[i].x, obstacles[i].y, 0.3);
            glutSolidSphere(0.3, 10, 10);
        glPopMatrix();
    }
    
}

void detecCollisionWihtObstacles(int i) {
    float   x_ball = -translationPar;
    float   y_ball = -1;

    if( sqrtf(
        powf(obstacles[i].x - x_ball,2) +
        powf(obstacles[i].y - y_ball,2)
        ) < 0.6){
        animation_ongoing=0;
        gameOver = 1;
        writeMessage();
    }
}

void writeScore() {
    glDisable(GL_LIGHTING);
    score+=speedPar*2;
    char s[18];
    sprintf(s,"Score : %.1f",score);
    int i, n = strlen(s);
    glPushMatrix();
        glColor3f(1, 1, 1);
        glRasterPos3f(-5.39, 8, 0);
        
        for(i = 0; i < n; i++){
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
        }
    glPopMatrix();
    glEnable(GL_LIGHTING);
}

void writeMessage() {
    glDisable(GL_LIGHTING);
    char *s = "GAME OVER";
    int i, n = strlen(s);
    glPushMatrix();
        glColor3f(1, 0, 0);
        glRasterPos3f(-0.38, 2, 1);
        
        for(i = 0; i < n; i++){
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
        }
    glPopMatrix();
    glEnable(GL_LIGHTING);
}

void writeLevelUp() {
    glDisable(GL_LIGHTING);
    char *s = "LEVEL UP";
    int i, n = strlen(s);
    glPushMatrix();
        glColor3f(0, 1, 0);
        glRasterPos3f(-0.32, 2, 1);
        
        for(i = 0; i < n; i++){
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
        }
    glPopMatrix();
    glEnable(GL_LIGHTING);
}

void writeLevel() {
    speedPar = 0.05 + 0.01*level;
    obstaclesPar = 0.01 + 0.002*level;
    glDisable(GL_LIGHTING);
    char s[12];
    sprintf(s,"Level : %d",level);
    int i, n = strlen(s);
    glPushMatrix();
        glColor3f(1, 1, 1);
        glRasterPos3f(-5, 7, 0);
        
        for(i = 0; i < n; i++){
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
        }
    glPopMatrix();
    glEnable(GL_LIGHTING);
}

void screen_size() {
    if (fullscreen == 0) {
        glutFullScreen();
        fullscreen = 1;
    }
    else {
        glutReshapeWindow(1000, 1000);
        fullscreen = 0;
    }
}
