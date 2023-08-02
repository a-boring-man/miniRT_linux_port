![](https://github.com/a-boring-man/miniRT_linux_port/blob/main/110_score_icon.png)

# miniRT_linux

This is a mid-course project at 42 School. The project requires us to build a basic ray tracer.

We had to implement basic shapes like spheres, planes, and cylinders, handle ambient luminosity, lights, and instructions from a file. We also had to implement rotation and translation for all objects and a moving camera.

## Bonus

There were multiple bonus features, including reflection, colored lights, and multiple spotlights.

## Use

This is the linux port.

0 : Requirements

  - Linux or last version of wsl2
  - apt-get install build-essentials to get gcc

miniRT_linux uses a linux version of minilibx

1 : make

2 : ./binary/miniRT map/****.rt

## control

C - goes into camera mode (the default mode frome where all other mode/control are available), this mode is available from all other mod and is use as a portal to change mod. You can control the camera using W and S to go forward or backward, right arrow key and left arrow key to turn right and left and up and down to pitch up and down.

you can move object using WS + the arroz key, change dimention using Q and E, rotate object using IJKL, and use + or - to switch to an other instances of that object.

F - to go into sphere control mod to control sphere.

P - to go into plane mod to controle plane.

R - to go into reflection controle: use + or - to change the depth of the reflection, up and down arrow to controle the intensity.

Y - to go into cylinder control mod to control cylinder: use Z and X to change the length of the cylinder and Q and E to change it's diameter.

B - to go into light control mod to control light.
