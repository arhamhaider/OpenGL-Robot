# OpenGL-Robot
This project implements a hierarchical 3D robot model using modern OpenGL and C++, designed to demonstrate core computer graphics concepts such as transformation hierarchies, animation, camera control, and basic lighting.
 
Camera also moves as you press it

How to Build:
mkdir build && cd build
cmake ..
make
./robot_demo

Quick Rebuild / Clean Build:
cd ..; rm -rf build; mkdir build && cd build; cmake ..; make; ./robot_demo;

Controls

- 1 toggle shoulder wave (arms swing in opposite phase).
- 2 toggle head yaw (side-to-side).
- 3 toggle torso twist (subtle rotation around Y).
- R reset arm/elbow angles and clear animation offsets.
- Existing manual controls:
- W/S shoulder up/down.
- E/D elbows bend/straighten.

Camera Controls

- Left / Right Arrow Keys orbit camera around robot.
- Up / Down Arrow Keys zoom in / out.
- F1 front view.
- F2 right-side view.
- F3 back view.
- F4 top view.
- F5 return to orbit mode.

