#ifndef UTILITY_H
#define UTILITY_H


#include <stdlib.h>
#include <GL/glut.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include "callback.h"
#include "keyboard.h"
#include "sharedVars.h"

//Moje funkcije
void updatePlayerJumpHeight();
int getPlayerCurrentTile();
void generateMoreGround();
bool canMoveThisWay(unsigned char key);
bool initGround(void);




#endif 