PROGRAM = 2d_platformer
CC      = gcc
ZAST    = -g -ansi -std=c99 -Wall -L/usr/X11R6/lib -L/usr/pkg/lib
PROG    = src/main.c src/utility.c src/callback.c
ZAV     = src/utility.h src/callback.h
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