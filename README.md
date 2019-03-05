# RT
A 3d raytracing program (42 team project)

Below are the features (current features are marked with '•' and projected features are marked with '-'):

# Features:
• Cross-platform (windows, mac, linux), using SDL2 and OpenCL
• Realtime (no unnecessary renders done, 60 fps - depending on the quality of render currently set and the GPU)
• OpenCL GPU acceleration, to lessen the usual lag of a raytracer (and maybe scale2x or hq2x if needed)
• Fully controllable camera, with all 3 clicks and/or arrow keys
• A configuration file to store properties between program executions
• UI pane allowing the user to modify any of the camera's properties
• UI pane allowing the user to modify any of the scene's properties
• UI list of objects within the scene with property expanding and scrollbar controls
• I/O functions accessible through the UI for file opening/importing and saving
• A random RT file generator
- Clipboard copy/pasting of data within the program
- Selecting objects on click, and moving/rot/scaling them with keys
x Skybox (currently background colors, or textured giant primitives can be used to this effect)

# Light Features:
• Primitive-shaped lights
• Monte-Carlo path-tracing
- Bi-directional path-tracing
• Reflection (mirror surfaces)
• Refraction (transparent surfaces)
• fresnel reflections (glassy surface highlighting)
- caustic lights (refractions on shadows)
- Black holes (ray curving)

# Primitives & Shapes:
• Plane (infinite, and finite rectangle and disk)
- Triangle
• Cube
• Sphere
• Cylinder (infinite, and finite)
• Cone (infinite and finite)
• Saddle
• Paraboloid
• Hyperboloid
- OBJ triangular mesh models (intersecting rays in world space)
- Mobius twist
- Torus knot
- 3D Epitrochoid/Hypocycloid
- Fractals
