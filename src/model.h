#ifndef MODEL_H
#define MODEL_H

#include <stdlib.h>
#include <GL/glut.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include "callback.h"
#include "utility.h"
#include "sharedVars.h"


//Funkcija za iscrtavanje igraca
void drawPlayerModel(float x, float y);

//Funkcije za iscrtavanje podloge
void drawGround2D();
void drawGround3D();

//Iscrtavanje prikaza energije igraca
void drawStaminaBar();

//Iscrtavanje dekoracija
void drawTree2D(float x, float y, int poz);
void drawChimney(int poz, float height, int option);
void drawHill(int poz, float height);
void drawMoon(void);
void drawLakes(void);

//Iscrtavanje kliping ravni od koje bezimo.
void drawRedPlane(void);


//Ispisivanje score counter-a
void writeScore(char *string,float x,float y,float z); 


#endif