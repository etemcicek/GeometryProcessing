# GeometryProcessing

Disk_parameterization;

Disk paramaterization is used to flatten face mesh object. In this project, uniform weights used to obtain flattening mesh. 
For preserving triangle shapes in mesh during flattening process, harmonic or mean-value weights might be used in laplacian matrix.

Simply solving sparse system, eigen library is used.
Displaying 2D face mesh, Fade2D Library (issued by Geom Software) is used.


Fade2D Library:http://www.geom.at
Eigen Library:http://eigen.tuxfamily.org/index.php?title=Main_Page


Hole Filling;

Hole filling method(Filling Holes in Meshes by Peter Liepa ) for simply patching holes of 3D bunny object is implemented in this project.

After patching process, Mesh smoothing is applied to holes' vertices by calculating avarage length of their 1-ring neighborhood.

Geodesic Distance Between Two Mesh Vertices(Dijkstra);

Geodesic distance between two mesh vertices is the length of the shortest path along the surface that connects the two vertices.

