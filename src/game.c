#include "../includes/game.h"
#include <math.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

float animationPar = 0;
float translationPar = 0;
double linesPoints[5] = {3.425, 2.4, 1.375, 0.35, -0.675};



void on_keyboard(unsigned char key, int x, int y)
{
    (void)x;
    (void)y;
        switch (key) {
        case 27:
            exit(0);
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

    gluLookAt(0, -4, 3, 0, 0, 0, 0, 1, 0);
    
    setLight();

    drawRoad();
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

    GLfloat ambientCoeffs[] = { 0.2, 0.02, 0.02, 1 };
    GLfloat diffuseCoeffs[] = { 0.7, 0.07, 0.07, 1 };
    GLfloat specularCoeffs[] = { 0.7, 0.6, 0.6, 1 };


    GLfloat shininess = 20;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambientCoeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseCoeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specularCoeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    glPushMatrix();
        glTranslatef(0, -1, 0);
        glTranslatef(-translationPar, 0, 0);
        glRotatef(-animationPar, 1, 0, 0);
        glutSolidSphere(0.3, 20, 20);
    glPopMatrix();
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
        glVertex3f(3, -3, -0.1);
        glVertex3f(-3, -3, -0.1);
        glVertex3f(-3, 25, -0.1);
        glVertex3f(3, 25, -0.1);
    glEnd();
    glPopMatrix();
    
    glDisable(GL_LIGHTING);
    
    glColor3f(1, 1, 1);
    

    int i;
    for(i = 0; i < 14; i++) {
        double x;
        x = -3 + i*2;
        glBegin(GL_POLYGON);
            glVertex3f(0.1,x, 0);
            glVertex3f(-0.1,x, 0);
            glVertex3f(-0.1,x+1.5, 0);
            glVertex3f(0.1,x+1.5, 0);
        glEnd();
    }
    glEnable(GL_LIGHTING);
}