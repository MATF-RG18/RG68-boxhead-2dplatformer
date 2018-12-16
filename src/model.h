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


//Funkcije za iscrtavanje igraca
void drawPlayerModel2D(void);
void drawPlayerModel3D(void);

//Funkcije za iscrtavanje podloge
void drawGround2D();
void drawGround3D();



#endif