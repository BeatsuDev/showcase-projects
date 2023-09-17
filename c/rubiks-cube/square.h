#ifndef FILE_SEEN_SQUARE
#define FILE_SEEN_SQUARE

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "types.h"

typedef struct {
    float size;
    RGBColor color;
} Square;

void draw_square(Square square)
{
    glColor3f(square.color.red, square.color.green, square.color.blue);
    glTranslated(-square.size / 2, -square.size / 2, 0);
    glBegin(GL_QUADS);
        glVertex2d(-square.size / 2, -square.size / 2);
        glVertex2d(-square.size / 2, square.size / 2);
        glVertex2d(square.size / 2, square.size / 2);
        glVertex2d(square.size / 2, -square.size / 2);
    glEnd();
    glFlush();
}

#endif