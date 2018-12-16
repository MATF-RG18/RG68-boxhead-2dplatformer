#ifndef CALLBACK_H
#define CALLBACK_H

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include "utility.h"
#include "sharedVars.h"
#include "keyboard.h"
#include "model.h"


void set_callback(void);
void on_timer(int value);
void on_reshape(int width, int height);
void on_display(void);

#endif