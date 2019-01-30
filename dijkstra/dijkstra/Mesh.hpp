//
//  Mesh1.hpp
//  Viewer
//
//  Created by Ethem Bilgehan CICEK on 4.12.2018.
//  Copyright © 2018 Ethem Bilgehan CICEK. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <stdio.h>

#include <iostream>
#include <vector>

using namespace std;

struct Vertex
{
    float* coords, * normals; //3d coordinates etc
    int idx; //who am i; verts[idx]
    
    vector< int > vertList; //adj vvertices;
    vector< int > triList;
    vector< int > edgeList;
    
    Vertex(int i, float* c) : idx(i), coords(c) {};
};

struct Edge
{
    int idx; //edges[idx]
    int v1i, v2i; //endpnts
    float length;
    Edge(int id, int v1, int v2,float distancee) : idx(id), v1i(v1), v2i(v2),length(distancee) { };
    
 //   void computeLength()
   // {
     //   length = 7;
    //}
};

struct Triangle
{
    int idx; //tris[idx]
    int v1i, v2i, v3i;
    Triangle(int id, int v1, int v2, int v3) : idx(id), v1i(v1), v2i(v2), v3i(v3) {};
};

class Mesh
{
private:
    void addTriangle(int v1, int v2, int v3);
    void addEdge(int v1, int v2);
    void addVertex(float x, float y, float z);
    bool makeVertsNeighbor(int v1i, int v2i);
public:
    vector< int > ShortestPath(int src, bool print = true);
    vector< int > getShortestPath(vector< int > &output, vector< int > pathList, int dest);
    void printGeoMatrix();
    void loadOff(const char* name);

    vector< Vertex* > verts;
    vector< Triangle* > tris;
    vector< Edge* > edges;
    
    
    Mesh() {} ;
    void createCube(float side);
    void loadOff(char* name);
};
static Mesh tmp;










#endif /* Mesh1_hpp */
