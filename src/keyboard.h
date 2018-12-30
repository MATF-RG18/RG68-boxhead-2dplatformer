#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include "utility.h"
#include "callback.h"
#include "sharedVars.h"

void setKeyboardFunc(void);
void on_keyboard(unsigned char key, int x, int y);
void on_release(unsigned char key, int x, int y);

#endif