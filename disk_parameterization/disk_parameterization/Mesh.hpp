//
//  Mesh.hpp
//  disk_parameterization
//
//  Created by Ethem Bilgehan CICEK on 15.12.2018.
//  Copyright © 2018 Ethem Bilgehan CICEK. All rights reserved.
//



#ifndef Mesh_hpp
#define Mesh_hpp

#include <stdio.h>
#include<iostream>
#include<vector>
#include<math.h>
#include<fstream>
#include<//opt/local/include/eigen3/eigen/core>

using namespace std;


struct compare_xy {
    bool operator ()(const pair<float, float>& left, const pair<float, float>& right) const {
        return (left.first < right.first) || ((left.first == right.first) && (left.second < right.second));
    }
};

struct Vertex
{
    
    float x,y,z,*normalss; //3d coordinates etc
    int idx;
    int idx1;//who am i; verts[idx]
    int normalid;
    vector< int > vertList; //adj vvertices;
    vector< int > triList;
    vector< int > edgeList;
    double *v1,*v2,*v3; //projection cordinates in 3 floating point
    
    
    Vertex(int i, float a,float b,float c) : idx(i) ,x(a),y(b),z(c) {};
    Vertex(float x1,float y1,float z1):x(x1),y(y1),z(z1){};
    Vertex(int x,float *norms):normalid(x),normalss(norms){};
    Vertex(int xx,int x,double *xx1,double *yy1,double *zz1): idx1(xx),idx(x),v1(xx1),v2(yy1),v3(zz1){};
    
};

struct Edge
{
    int idx; //edges[idx]
    int v1i, v2i; //endpnts
    float length;
    Edge(int id, int v1, int v2) : idx(id), v1i(v1), v2i(v2) {  };
    Edge(int a1,int a2):v1i(a1),v2i(a2){};
    ~Edge(){};
    vector<int > neighbors;
  
    
    
};

struct Triangle
{
    //tris[idx]
    int v1i, v2i, v3i;
    int idx;
    float *normals;
    Triangle(int id,int v1, int v2, int v3) : idx(id),v1i(v1), v2i(v2), v3i(v3) {};
    
};


class Mesh
{
private:
    void addTriangle(int v1, int v2, int v3);
    void addEdge(int v1, int v2);
    void addVertex(float x, float y, float z);
    bool makeVertsNeighbor(int v1i, int v2i);

    
    
public:
    
    vector< Vertex* > verts;
    vector< Triangle* > tris;
    vector< Edge* > edges;

    
    vector<Edge* > paired;
    vector<Edge* > borders;
    vector<int> bordersInto;
    Mesh(){};
    

    void createCube(float side);
    void loadOff(char* name);
    
    void FindBorder();
    void MatrixMultip();
    void Draw( );
   
};
inline double dist(float x,float y,float x1,float y1){
    
    return sqrt((x-x1)*(x-x1)+(y-y1)*(y-y1));
    
}
inline bool func_name(pair<float, float> &p1, pair<float, float> &p2)
{
   // if(p1.second < p2.second )
     //   return 0;
    return p1.second<p2.second;  /////////1;
}
static Mesh tmp;


#endif /* Mesh_hpp */
