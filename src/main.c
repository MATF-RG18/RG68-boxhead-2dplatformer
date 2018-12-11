#include <stdlib.h>
#include <GL/glut.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include "callback.h"
#include "utility.h"


int main(int argc, char **argv)
{
    
    // Inicijalizujemo GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    // Kreiramo prozor
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    set_callback();

    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    

    initGround();
    
    //Glavna petlja
    glutMainLoop();

    return 0;
}




