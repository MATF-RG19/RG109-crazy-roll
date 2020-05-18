#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include "../includes/game.h"

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    initialize();   

    initialValues();
    
    glutMainLoop();
    return 0;
}