#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glut.h>

#include "square.h"
#include "rubiks_cube.h"

const int window_width = 1200;
const int window_height = 640;

unsigned int fps_start = 0;
unsigned int fps_frames = 0;

float distance = 15.0f;
float angleX = 3.1415926 / 2;
float angleY = 0.0f;
int lastX = 0;
int lastY = 0;

// Globals relating to rotation animation
int rotating = 0;
float rotation_speed = 4.5f;

struct rotation_animation {
    void (*rotation_function)(RubiksCube2x2 cube, float rotation);
    float rotation;
    float rotation_speed;
};

struct rotation_animation top_rotation = { cube_rotation_top, 0.0f, 0.0f };
float front_rotation = 0.0f;  // TODO: Implement
float right_rotation = 0.0f;  // TODO: Implement
float back_rotation = 0.0f;  // TODO: Implement
float left_rotation = 0.0f;  // TODO: Implement
struct rotation_animation bottom_rotation = { cube_rotation_top, 0.0f, 0.0f };


long draw_count = 0;
RubiksCube2x2 cube;

void motion(int x, int y) {
    //calculate the change in mouse position
    int dx = x - lastX;
    int dy = y - lastY;

    //update the last mouse position
    lastX = x;
    lastY = y;

    if (dx > 5 || dy > 5) return;  // Ignore big jumps

    //update the angles based on the mouse movement
    angleX += dx * 0.01f;
    angleY += dy * 0.01f;

    //clamp the angles to avoid gimbal lock
    if(angleY > 3.14159/2) angleY = 3.14159/2;
    if(angleY < -3.14159/2) angleY = -3.14159/2;

    //redraw the scene
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27: // Escape key
            exit(0);
            break;
        case 'a':
            rotating = 1;
            top_rotation.rotation_speed = -rotation_speed;
            break;
        case 'd':
            rotating = 1;
            top_rotation.rotation_speed = rotation_speed;
            break;
    }
}

void specialKeys(int key, int x, int y)
{
    if (rotating) return;
    switch (key)
    {
        case GLUT_KEY_LEFT: // Left arrow
            rotating = 1;
            bottom_rotation.rotation_speed = -rotation_speed;
            break;
        case GLUT_KEY_UP: // Up arrow
            rotate_right(cube, 1);
            break;
        case GLUT_KEY_RIGHT: // Right arrow
            rotating = 1;
            bottom_rotation.rotation_speed = rotation_speed;
            break;
        case GLUT_KEY_DOWN: // Down arrow
            rotate_right(cube, 3);
            break;
    }
}

void drawAxis()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
        // Draw x-axis in red
        glColor3f(1.0, 1.0, 1.0);
        glVertex3f(-5.0, 0.0, 0.0);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(5.0, 0.0, 0.0);

        // Draw y-axis in green
        glColor3f(1.0, 1.0, 1.0);
        glVertex3f(0.0, -5.0, 0.0);
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(0.0, 5.0, 0.0);

        // Draw z-axis in blue
        glColor3f(1.0, 1.0, 1.0);
        glVertex3f(0.0, 0.0, -5.0);
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(0.0, 0.0, 5.0);
    glEnd();
    glFlush();
}

void display()
{
    draw_count++;

    // Set perspective
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)window_width / (GLfloat)window_height, 0.1f, 50.0f);
    gluLookAt(
        distance * cos(angleX) * cos(angleY),
        distance * sin(angleY),
        distance * sin(angleX) * cos(angleY),
        0, 0, 0,
        0, 1, 0
    );

    // Reset everything
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Finally some DRAWING!!
    drawAxis();
    if (!rotating) draw_rubiks_cube_2x2x2(cube);

    // Handling top rotations
    if (!(top_rotation.rotation_speed == 0.0f))
    {
        top_rotation.rotation += top_rotation.rotation_speed;
        top_rotation.rotation_function(cube, top_rotation.rotation);

        if (top_rotation.rotation <= -90.0f)
        {
            top_rotation.rotation = 0.0f;
            top_rotation.rotation_speed = 0.0f;
            rotating = 0;
            rotate_top(cube, 1);
        }

        if (top_rotation.rotation >= 90.0f)
        {
            top_rotation.rotation = 0.0f;
            top_rotation.rotation_speed = 0.0f;
            rotating = 0;
            rotate_top(cube, 3);
        }
    }

    // Handling bottom rotations
    if (!(bottom_rotation.rotation_speed == 0.0f))
    {
        bottom_rotation.rotation += bottom_rotation.rotation_speed;
	glRotated(bottom_rotation.rotation, 0, 1, 0);
        bottom_rotation.rotation_function(cube, -bottom_rotation.rotation);

        if (bottom_rotation.rotation <= -90.0f)
        {
            bottom_rotation.rotation = 0.0f;
            bottom_rotation.rotation_speed = 0.0f;
            rotating = 0;
            rotate_bottom(cube, 3);
        }

        if (bottom_rotation.rotation >= 90.0f)
        {
            bottom_rotation.rotation = 0.0f;
            bottom_rotation.rotation_speed = 0.0f;
            rotating = 0;
            rotate_bottom(cube, 1);
        }
    }

    // Finito 
    glutPostRedisplay();
    glutSwapBuffers();
}

void init()
{
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)window_width / (GLfloat)window_height, 0.1f, 20.0f);
    cube = create_rubiks_cube_2x2x2(4);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(window_width, window_height);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow ("My rubiks cube!");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutMotionFunc(motion);
    glClearColor(0.0, 0.0, 0.0, 1.0);

    init();
    glutMainLoop(); // Infinite event loop
    return 0;
}
