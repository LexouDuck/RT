# RT
A 3d raytracing program (42 team project)

![rt.gif](GIF.gif)

Exported BMP image of render by Monte-Carlo path tracing with a ray-per-pixel amount  of 1024 and a depth of 24

![render_lego.bmp](render_lego.bmp)

Below are the features (current features are marked with '•' and projected features are marked with '-'):

# Building

Run `make`.

  - Linux:

    - If you get a compilation error of the kind `#include <CL/cl.h> not found`, check that `opencl-c-headers` are installed on your machine.
    - If you get a linking error of the kind `cannot find -lSDL2: No such file or directory`, check that `libsdl2-dev` is installed on your machine
    - If you get a linking error of the kind `cannot find -lOpenCL: No such file or directory`, check that  `ocl-icd-opencl-dev` is installed on your machine.
    - If you get a an "OpenCL error -1001", you probably have an NVIDIA graphics card, and there's probably an issue with how your GPU drivers are configured. Follow the guide [here](https://askubuntu.com/questions/1270341/nvidia-driver-390-broken-dependencies-install-preventing-uninstall-or-new-instal), but download the driver that's actually recommended for your platform (as of writing this, it was `nvidia-driver-550-server-open` for mine).

  - Mac OS: [TODO]

  - Windows: [TODO]


# Features:
* Cross-platform (windows, mac, linux), using SDL2 and OpenCL
* Realtime (no unnecessary renders done, 60 fps - of course, this also depends on the quality of render currently set, and your GPU)
* OpenCL GPU acceleration, to lessen the usual lag of a raytracer (and maybe scale2x or hq2x if needed)
* Various render modes, for debug (normal map, bbox, etc) or quality.
* Fully controllable camera, with all 3 clicks and/or arrow keys
* A configuration file to store properties between program executions
* UI pane allowing the user to modify any of the camera's properties
* UI pane allowing the user to modify any of the scene's properties
* UI list of objects within the scene with property expanding and scrollbar controls
* I/O functions accessible through the UI for file opening/importing and saving
* A random RT file generator
* [TODO] Clipboard copy/pasting of data within the program
* [TODO] Selecting objects on click, and moving/rot/scaling them with keys
* [TODO] Skybox (currently background colors, or textured giant primitives can be used to this effect)

# Light Features:
* Primitive-shaped lights
* Monte-Carlo path-tracing
* Reflection (mirror surfaces)
* Refraction (transparent surfaces)
* fresnel reflections (glassy surface highlighting)
* [TODO] Bi-directional path-tracing
* [TODO] caustic lights (refractions on shadows)
* [TODO] Black holes (ray curving)

# Primitives & Shapes:
* Plane (infinite, and finite rectangle and disk)
* Triangle
* Cube
* Sphere
* Cylinder (infinite, and finite)
* Cone (infinite and finite)
* Saddle
* Paraboloid
* Hyperboloid
* [TODO] OBJ triangular mesh models (intersecting rays in world space)
* [TODO] Mobius twist
* [TODO] Torus knot
* [TODO] 3D Epitrochoid/Hypocycloid
* [TODO] Fractals
* [TODO] Unions, intersections, and their negative counterparts

# Structure
* [TODO] fix to go beyond the dumb structural requirements of 42
