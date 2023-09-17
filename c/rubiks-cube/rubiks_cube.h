#ifndef FILE_RUBIKS_CUBE_SEEN
#define FILE_RUBIKS_CUBE_SEEN

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "square.h"
#include "types.h"


// A corner piece has 3 visible faces with different colors each
typedef struct corner_piece
{
    float size;
    Square top_face;
    Square right_face;
    Square front_face;
} CornerPiece;

typedef struct rubiks_cube_2x2x2
{
    int size;

    // Objects are stored here
    CornerPiece *pieces;

    // Store in two layers for simpler indexing when moving
    // around the corner pieces when rotating the faces
    
    // These are arrays of pointers that point to the pieces array
    CornerPiece **top_layer;
    CornerPiece **bottom_layer;

} RubiksCube2x2;

CornerPiece create_corner_piece(float size, RGBColor top_color, RGBColor right_color, RGBColor front_color)
{
    CornerPiece piece;
    piece.size = size;

    piece.top_face = (Square) { size, top_color };
    piece.right_face = (Square) { size, right_color };
    piece.front_face = (Square) { size, front_color };

    return piece;
}

void draw_corner_piece(CornerPiece piece)
{
    RGBColor frame_color = (RGBColor) { 0.3, 0.3, 0.3 };
    // Draw the piece frame
    glPushMatrix();
        glColor3f(frame_color.red -0.15, frame_color.green -0.15 , frame_color.blue -0.15);
        glTranslated(piece.size / 2.0, piece.size / 2.0, piece.size / 2.0);
        glutWireCube(piece.size);
    glPopMatrix();
    
    // Draw the top face
    glPushMatrix();
        glTranslated(piece.size, piece.size, piece.size);
        glPushMatrix();
            glRotated(90, 1, 0, 0);
            draw_square(piece.top_face);
        glPopMatrix();

        // Draw the right face
        glPushMatrix();
            glRotated(-90, 0, 1, 0);
            draw_square(piece.right_face);
        glPopMatrix();

        // Draw the front face
        glPushMatrix();
            draw_square(piece.front_face);
        glPopMatrix();

        // Draw the bottom face (frame color)
        glPushMatrix();
            glTranslated(0, -piece.size, -piece.size);
            glRotated(-90, 1, 0, 0);
            draw_square((Square) { piece.size, frame_color });
        glPopMatrix();

        // Draw the left face (frame color)
        glPushMatrix();
            glTranslated(-piece.size, 0, -piece.size);
            glRotated(90, 0, 1, 0);
            draw_square((Square) { piece.size, frame_color });
        glPopMatrix();

        // Draw the back face (frame color)
        glPushMatrix();
            glTranslated(0, -piece.size, -piece.size);
            glRotated(180, 1, 0, 0);
            draw_square((Square) { piece.size, frame_color });
        glPopMatrix();
    glPopMatrix();
}

RubiksCube2x2 create_rubiks_cube_2x2x2(int size)
{
    int side_length = size / 2;

    // Create the top layer corner pieces start from top front right and going clockwise
    // All pieces are created in the top front right position and then rotated to their
    // correct position around the y-axis
    CornerPiece top_front_right = create_corner_piece(
        side_length,
        (RGBColor) { 1, 1, 1 },
        (RGBColor) { 1, 0, 0 },
        (RGBColor) { 0, 1, 0 }
    );

    CornerPiece top_front_left = create_corner_piece(
        side_length,
        (RGBColor) { 1, 1, 1 },
        (RGBColor) { 0, 1, 0 },
        (RGBColor) { 1, 0.5, 0 }
    );

    CornerPiece top_back_left = create_corner_piece(
        side_length,
        (RGBColor) { 1, 1, 1 },
        (RGBColor) { 1, 0.5, 0 },
        (RGBColor) { 0, 0, 1 }
    );

    CornerPiece top_back_right = create_corner_piece(
        side_length,
        (RGBColor) { 1, 1, 1 },
        (RGBColor) { 0, 0, 1 },
        (RGBColor) { 1, 0, 0 }
    );

    // Create the bottom layer corner pieces
    // Pieces are created in the top front right position, then rotated 180 degrees around the z-axis
    // and then rotated around the y-axis to their correct position
    CornerPiece bottom_front_left = create_corner_piece(
        side_length,
        (RGBColor) { 1, 1, 0 },
        (RGBColor) { 1, 0.5, 0 },
        (RGBColor) { 0, 1, 0 }
    );

    CornerPiece bottom_front_right = create_corner_piece(
        side_length,
        (RGBColor) { 1, 1, 0 },
        (RGBColor) { 0, 1, 0 },
        (RGBColor) { 1, 0, 0 }
    );

    CornerPiece bottom_back_right = create_corner_piece(
        side_length,
        (RGBColor) { 1, 1, 0 },
        (RGBColor) { 1, 0, 0 },
        (RGBColor) { 0, 0, 1 }
    );

    CornerPiece bottom_back_left = create_corner_piece(
        side_length,
        (RGBColor) { 1, 1, 0 },
        (RGBColor) { 0, 0, 1 },
        (RGBColor) { 1, 0.5, 0 }
    );

    CornerPiece *pieces = malloc(sizeof(CornerPiece) * 8);

    pieces[0] = top_front_right;
    pieces[1] = top_front_left;
    pieces[2] = top_back_left;
    pieces[3] = top_back_right;
    pieces[4] = bottom_front_left;
    pieces[5] = bottom_front_right;
    pieces[6] = bottom_back_right;
    pieces[7] = bottom_back_left;

    CornerPiece **top_layer = malloc(sizeof(CornerPiece *) * 4);
    CornerPiece **bottom_layer = malloc(sizeof(CornerPiece *) * 4);

    top_layer[0] = &pieces[0];
    top_layer[1] = &pieces[1];
    top_layer[2] = &pieces[2];
    top_layer[3] = &pieces[3];

    bottom_layer[0] = &pieces[4];
    bottom_layer[1] = &pieces[5];
    bottom_layer[2] = &pieces[6];
    bottom_layer[3] = &pieces[7];

    RubiksCube2x2 cube;
    cube.size = size;
    cube.pieces = pieces;
    cube.top_layer = top_layer;
    cube.bottom_layer = bottom_layer;

    return cube;
}

void destroyCube(RubiksCube2x2 cube)
{
    free(cube.pieces);
    free(cube.top_layer);
    free(cube.bottom_layer);
}

void draw_rubiks_cube_2x2x2(RubiksCube2x2 cube)
{
    // Draw the top layer
    glPushMatrix();
        draw_corner_piece(*cube.top_layer[0]);

        glRotated(-90, 0, 1, 0);
        draw_corner_piece(*cube.top_layer[1]);

        glRotated(-90, 0, 1, 0);
        draw_corner_piece(*cube.top_layer[2]);

        glRotated(-90, 0, 1, 0);
        draw_corner_piece(*cube.top_layer[3]);
    glPopMatrix();

    // Draw the bottom layer
    glPushMatrix();
        glRotated(180, 0, 0, 1);
        draw_corner_piece(*cube.bottom_layer[0]);

        glRotated(-90, 0, 1, 0);
        draw_corner_piece(*cube.bottom_layer[1]);

        glRotated(-90, 0, 1, 0);
        draw_corner_piece(*cube.bottom_layer[2]);

        glRotated(-90, 0, 1, 0);
        draw_corner_piece(*cube.bottom_layer[3]);
    glPopMatrix();
}

// ################# ROTATIONS #################
/**
 * Moves the pieces in cube.top_layer to the new positions after <rotations> rotations.
 * 
 * @param cube       The cube to rotate.
 * @param rotations  The number of rotations to perform.
*/
void rotate_top(RubiksCube2x2 cube, unsigned int rotations)
{
    for (unsigned int i = 0; i < rotations; i++)
    {
        CornerPiece *temp = cube.top_layer[3];
        cube.top_layer[3] = cube.top_layer[2];
        cube.top_layer[2] = cube.top_layer[1];
        cube.top_layer[1] = cube.top_layer[0];
        cube.top_layer[0] = temp;
    }
}

/**
 * Moves the pieces in cube.bottom_layer to the new positions after <rotations> rotations.
 * 
 * @param cube       The cube to rotate.
 * @param rotations  The number of rotations to perform.
*/
void rotate_bottom(RubiksCube2x2 cube, unsigned int rotations)
{
    for (unsigned int i = 0; i < rotations; i++)
    {
        CornerPiece *temp = cube.bottom_layer[3];
        cube.bottom_layer[3] = cube.bottom_layer[2];
        cube.bottom_layer[2] = cube.bottom_layer[1];
        cube.bottom_layer[1] = cube.bottom_layer[0];
        cube.bottom_layer[0] = temp;
    }
}

void rotate_right(RubiksCube2x2 cube, unsigned int rotations)
{
    for (unsigned int i = 0; i < rotations; i++)
    {
        CornerPiece *temp = cube.top_layer[3];
        cube.top_layer[3] = cube.top_layer[0];
        cube.top_layer[0] = cube.bottom_layer[1];
        cube.bottom_layer[1] = cube.bottom_layer[2];
        cube.bottom_layer[2] = temp;

        // Fix the colors of the pieces on the top layer...
        RGBColor temp0 = cube.top_layer[3]->top_face.color;
        cube.top_layer[3]->top_face.color = cube.top_layer[3]->front_face.color;
        cube.top_layer[3]->front_face.color = cube.top_layer[3]->right_face.color;
        cube.top_layer[3]->right_face.color = temp0;

        RGBColor temp1 = cube.top_layer[0]->top_face.color;
        cube.top_layer[0]->top_face.color = cube.top_layer[0]->right_face.color;
        cube.top_layer[0]->right_face.color = cube.top_layer[0]->front_face.color;
        cube.top_layer[0]->front_face.color = temp1;

        // Fix bottom layer
        RGBColor temp2 = cube.bottom_layer[1]->top_face.color;
        cube.bottom_layer[1]->top_face.color = cube.bottom_layer[1]->front_face.color;
        cube.bottom_layer[1]->front_face.color = cube.bottom_layer[1]->right_face.color;
        cube.bottom_layer[1]->right_face.color = temp2;

        RGBColor temp3 = cube.bottom_layer[2]->top_face.color;
        cube.bottom_layer[2]->top_face.color = cube.bottom_layer[2]->right_face.color;
        cube.bottom_layer[2]->right_face.color = cube.bottom_layer[2]->front_face.color;
        cube.bottom_layer[2]->front_face.color = temp3;
    }
}

/**
 * A modified version of the draw_cube function that draws the cube in a rotated state.
 * 
 * @param cube      The cube to rotate.
 * @param rotation  The rotation of the top layer in degrees clockwise.
 */
void cube_rotation_top(RubiksCube2x2 cube, float rotation)
{
    // Draw the top layer
    glPushMatrix();
        glRotated(rotation, 0, 1, 0);
        draw_corner_piece(*cube.top_layer[0]);

        glRotated(-90, 0, 1, 0);
        draw_corner_piece(*cube.top_layer[1]);

        glRotated(-90, 0, 1, 0);
        draw_corner_piece(*cube.top_layer[2]);

        glRotated(-90, 0, 1, 0);
        draw_corner_piece(*cube.top_layer[3]);
    glPopMatrix();

    // Draw the bottom layer
    glPushMatrix();
        glRotated(180, 0, 0, 1);
        draw_corner_piece(*cube.bottom_layer[0]);

        glRotated(-90, 0, 1, 0);
        draw_corner_piece(*cube.bottom_layer[1]);

        glRotated(-90, 0, 1, 0);
        draw_corner_piece(*cube.bottom_layer[2]);

        glRotated(-90, 0, 1, 0);
        draw_corner_piece(*cube.bottom_layer[3]);
    glPopMatrix();
}

/**
 * A modified version of the draw_cube function that draws the cube in a rotated state.
 * 
 * @param cube      The cube to rotate.
 * @param rotation  The rotation of the bottom layer in degrees clockwise.
 */
void cube_rotation_bottom(RubiksCube2x2 cube, float rotation)
{
    glRotated(-rotation, 0, 1, 0);
    cube_rotation_top(cube, rotation);
}

#endif
