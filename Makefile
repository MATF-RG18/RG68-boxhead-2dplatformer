PROGRAM = 2d_platformer
CC      = gcc
ZAST    = -g -std=c99 -Wall -L/usr/X11R6/lib -L/usr/pkg/lib
PROG    = src/main.c src/utility.c src/callback.c src/keyboard.c src/sharedVars.c src/model.c
ZAV     = src/utility.h src/callback.h src/keyboard.h src/sharedVars.h src/model.h
BIBL    = -lglut -lGLU -lGL -lm

$(PROGRAM): $(PROG) $(ZAV)
	$(CC) $(ZAST) -o $(PROGRAM) $(PROG) $(BIBL)

.PHONY: run makerun clean

run:
	./$(PROGRAM) &

makerun:
	make
	make run

clean:
	rm -f *~ src/*~ screenshots/*~