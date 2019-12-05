#include "../includes/game.h"
#include <math.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

float animationPar = 0;
float translationPar = 0;


void on_keyboard(unsigned char key, int x, int y)
{
    (void)x;
    (void)y;
    (void)key;
    //TODO
}

void setLight()
{
    //TODO
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

    gluLookAt(0, -1, 3, 0, 0, 0, 0, 1, 0);
    
    setLight();

    drawBall();

    glutSwapBuffers();
}

void initialize(void)
{
    srand(time(NULL));
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowSize(1000, 1000);

    glutInitWindowPosition(400, 500);
    glutCreateWindow("Crazy roll");
    
    glutKeyboardFunc(on_keyboard);
    
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);
    
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    
}

void drawBall(void)
{
    
     GLfloat ambientCoeffs[] = { 0.0215, 0.1745, 0.0215, 1 };
     GLfloat diffuseCoeffs[] = { 0.07568, 0.61424, 0.07568, 1 };
     GLfloat specularCoeffs[] = { 0.633, 0.727811, 0.633, 1 };
    
    GLfloat shininess = 100;
    
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    glPushMatrix();
        glTranslatef(0, -1, 0);
        glTranslatef(-translationPar, 0, 0);
        glRotatef(-animationPar, 1, 0, 0);
        glutSolidSphere(0.2, 20, 20);
    glPopMatrix();
}