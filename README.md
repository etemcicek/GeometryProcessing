# GeometryProcessing

Disk_parameterization;

Disk paramaterization is used to flatten face mesh object. In this project, uniform weights used to obtain flattening mesh. 
For preserving triangle shapes in mesh during flattening process, harmonic or mean-value weights might be used in laplacian matrix.

Simply solving sparse system, eigen library is used.
Displaying 2D face mesh, Fade2D Library (issued by Geom Software) is used.


Fade2D Library:http://www.geom.at
Eigen Library:http://eigen.tuxfamily.org/index.php?title=Main_Page

Input:

<img width="636" alt="3dface" src="https://user-images.githubusercontent.com/36789930/52198992-d1f09380-2875-11e9-8fe4-5965cbc7a87e.png">

Output:

<img width="684" alt="flattenedface" src="https://user-images.githubusercontent.com/36789930/52199011-e46acd00-2875-11e9-9149-7c1339492586.png">


Hole Filling;

Hole filling method(Filling Holes in Meshes by Peter Liepa ) for simply patching holes of 3D bunny object is implemented in this project.

After patching process, Mesh smoothing is applied to holes' vertices by calculating avarage length of their 1-ring neighborhood.

Before Triangulation:

<img width="636" alt="bunnyholes" src="https://user-images.githubusercontent.com/36789930/52199167-54795300-2876-11e9-8de9-ee67f1115b21.png">

After Triangulation:

<img width="642" alt="triangulationofholes" src="https://user-images.githubusercontent.com/36789930/52199182-5fcc7e80-2876-11e9-8d5b-65f5aad3fbb7.png">

Refinement:

<img width="642" alt="refinement" src="https://user-images.githubusercontent.com/36789930/52199199-71158b00-2876-11e9-81a5-e1cc26673cd0.png">

Smoothing:

<img width="641" alt="smoothing" src="https://user-images.githubusercontent.com/36789930/52199217-7e327a00-2876-11e9-981f-857eaba671f9.png">



Geodesic Distance Between Two Mesh Vertices(Dijkstra);

Geodesic distance between two mesh vertices is the length of the shortest path along the surface that connects the two vertices.

Shortest Path:

<img width="799" alt="shortestpath" src="https://user-images.githubusercontent.com/36789930/52199262-a15d2980-2876-11e9-83bd-3d282607224e.png">

