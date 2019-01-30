//
//  Mesh.hpp
//  HoleFill
//
//  Created by Ethem Bilgehan CICEK on 4.01.2019.
//  Copyright © 2019 Ethem Bilgehan CICEK. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <stdio.h>
#include<iostream>
#include<vector>
#include<math.h>
#include<fstream>

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
    Edge(int id, int v1, int v2,float ll) : idx(id), v1i(v1), v2i(v2), length(ll) { };
    
 /*   void computeLength()
{
        length = 5;
    }*/
};

struct Triangle
{
    int idx; //tris[idx]
    int v1i, v2i, v3i;
    Triangle(int id, int v1, int v2, int v3) : idx(id), v1i(v1), v2i(v2), v3i(v3) {};
    Triangle(int v11,int v22,int v33): v1i(v11) ,   v2i(v22)   ,v3i(v33){};
};

class Mesh
{
public:
    void addTriangle(int v1, int v2, int v3);
    void addEdge(int v1, int v2);
    int addVertex(float* coords);
    bool makeVertsNeighbor(int v1i, int v2i);
    bool isBoundary(Vertex *v1,Vertex *v2);
    
    float distanceBetween(float* a, float* b);
    void removeTriangle(int v1i, int v2i, int v3i);
    bool triangleExists(int v1i, int v2i, int v3i);
    void splitTriangle(int idx);
    bool makeVertsUnneighbors(int v, int w);


public:
    void removeEdge(int a, int b);

    vector< Vertex* > verts;
    vector< Triangle* > tris;
    vector< Edge* > edges;
    vector<Triangle*>d_holes;
    vector<Triangle*>d2_holes;
    void FindHoles();

    Mesh() {} ;
    void createCube(float side);
    void loadOff(char* name);
};
static Mesh tmp;


#endif /* Mesh_hpp */
