This solution is for exercise 3 in the subject Extended Reality (XR) IDATT2505 at NTNU, 2023.

The task here was to create a rotatable rubiks cube using OpenGL. To get this running, you must install
freeglut3-dev `sudo apt install freeglut3-dev`. You might also need more libraries... Tested only on
Ubuntu Budgie 22.04

Compile with gcc: `gcc -lGL -lGLU -lglut -o main main.c`

Not all rotation animations were finished implemented, but the rotations should work (just without
animations). This project was only to get started with OpenGL, and once I got
the hang of very basic operations in OpenGL, I decided to move on instead of finishing the project.

To rotate the faces, use w and s for left rotations, a and d for top rotations, up and down arrows
for right rotations, and left and right arrows for bottom rotations.

