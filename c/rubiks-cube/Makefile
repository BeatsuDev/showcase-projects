# Makefile for compiling a C file with OpenGL and GLUT libraries

CC = gcc
CFLAGS = -Wall
LIBS = -ldl -lm -lGL -lGLU -lglut

SRCS = $(wildcard *.c)
BINS = $(SRCS:.c=)

all: $(BINS)

%: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

clean:
	rm -f $(BINS)

run:
	./$(BINS)
