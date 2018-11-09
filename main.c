#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>


//Cuvamo dimenzije prozora kao width i height
static int window_width, window_height; 

// Deklaracije callback funkcija. 
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void);
static void on_timer(int value);

int main(int argc, char **argv)
{
    // Inicijalizujemo GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    // Kreiramo prozor
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    // Postavljamo funkcije za registrovanje callback funkcija 
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);

    // Inicijalizujemo boju prozora i gl inicijalizacija
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);

    //Glavna petlja
    glutMainLoop();

    return 0;
}

static void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        /* Zavrsava se program. */
        exit(0);
        break;
    }
}

static void on_reshape(int width, int height)
{
     /* Pamte se sirina i visina prozora. */
    window_width = width;
    window_height = height;
}

static void on_display(void)
{
    //cistimo bafere
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Podesava se viewport
    glViewport(0, 0, window_width, window_height);

    // Podesava se projekcija. 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 1, 10);

    // Podesava se vidna tacka
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(1, 2, 3, 0, 0, 0, 0, 1, 0);

    // Skaliramo sve za koeficijent 2, po svim osama 
    glScalef(3, 3, 3);

    //Crtam cajnik
    glTranslatef(0, 0, 0);
            glColor3f(1, 1, 1);
            glutWireTeapot(0.5);
        glTranslatef(-1, 0, 0);

    glutSwapBuffers();
}

static void on_timer(int value)
{
    //za sada prazna
}