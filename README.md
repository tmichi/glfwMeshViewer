glfwMeshViewer
==============

A minimum example of mesh viewer with Eigen, glfw and OpenGL.


Requirement
-----------
- Eigen http://eigen.tuxfamily.org 
- GLFW http://www.glfw.org
- OpenGL and GLU
- CMake http://www.cmake.org (I use this for creating *sln and *vcproj files. You can build this project by creating project files manually.)

How to build (Windows)
-----------------------

- Copy header directories (Eigen/, GLFW/ ) to include/
- Copy *.lib to lib/
- Copy *.dll to C:¥Windows¥SysWoW64 (64bit windows). 
- Create build directory and create VS project files there. 

glfwMeshViewer
--------------
This is a simple mesh viewer with arc-ball rotations. type glfwMeshViewer.exe input.obj to execute. 

License 
-------
BSD license (See LICENSE.txt)

Contact 
-------
Takashi Michikawa (michikawa@acm.org)





