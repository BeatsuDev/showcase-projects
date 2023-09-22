# Javascript 3D Engine
Around the end of 2021, I was really interested in computer graphics rendering.
Without having any knowledge of how rendering actually worked, and only a very
basic experience using Unity, I ventured out on this project to create my very
own 3D Engine in JavaScript. 

I chose JavaScript because it was the easiest to draw to a screen with, needing
only to use a canvas. In the long run, it would also be easy to port as a desktop
app with electron.js.

# Notes
This is before I learned about matrixes, and rotation matrixes etc. My approach
and solution is therefore uses only trigonometry and euler angles. For some reason
the rendering fails to show the cube correctly when walking around it... However
moving up and down seems to work ok.

Use wasd to move around and ctrl + shift to go up and down. Look around with
the mouse while holding down left or right click.