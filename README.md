# FDF
My first graphic project on C | UNIT Factory | Creating a simplified 3D graphic representation of a relief landscape

In this project I discovered the basics of graphic programming, and in particular how to place points in space, how to join them with segments and most importantly how to observe the scene from a particular viewpoint.

- Graphic library *miniLibX*  was used. This library was developed internally and includes the minimum necessary to open a window, light a pixel and deal with events linked to this window: keyboard and mouse.

- The coordinates of this landscape are stored in a file passed as a parameter to your program.
Example:
$>cat 42.fdf
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0 10 10  0  0 10 10  0  0  0 10 10 10 10 10  0  0  0
0  0 10 10  0  0 10 10  0  0  0  0  0  0  0 10 10  0  0
0  0 10 10  0  0 10 10  0  0  0  0  0  0  0 10 10  0  0
0  0 10 10 10 10 10 10  0  0  0  0 10 10 10 10  0  0  0
0  0  0 10 10 10 10 10  0  0  0 10 10  0  0  0  0  0  0
0  0  0  0  0  0 10 10  0  0  0 10 10  0  0  0  0  0  0
0  0  0  0  0  0 10 10  0  0  0 10 10 10 10 10 10  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0

BONUS PART:
- color depends on z coordinate (press the **С key** while the program is running);
- rotation, translation, scale;
- advanced map parcing;
- color gradient.

<iframe width="560" height="315" src="https://www.youtube.com/embed/iYTB0YsdWOk" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>
