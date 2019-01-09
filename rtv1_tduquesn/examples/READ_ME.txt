I) Current (2019-01-09) parser line order for objects:
-material (int)
-pos (vec3)
-scl (vec3)
-rgb (vec3 [0., 1.]^3)
-specul (vec3 ~[0.5, 5.]^3)
-intensity (1. for normal objects, much higher for light spots)

II) Materials:
- lightsrc == 0
- diffuse == 1
- mirror == 2
- glassy == 3
- glossy == 4

III) Camera:
- anchor (vec3)
- polar pos (vec3)
