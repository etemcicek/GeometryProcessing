//
//  Mesh.cpp
//  HoleFill
//
//  Created by Ethem Bilgehan CICEK on 4.01.2019.
//  Copyright © 2019 Ethem Bilgehan CICEK. All rights reserved.
//

#include "Mesh.hpp"
#include <iostream>
#include <fstream>
#include <functional>
#include <queue>
#include <cmath>
#include <limits>

void Mesh::loadOff(char* name)
{
FILE* fPtr = fopen(name, "r");
char str[334];

fscanf(fPtr, "%s", str);

int nVerts, nTris, n, i = 0;
float x, y, z;

fscanf(fPtr, "%d %d %d\n", &nVerts, &nTris, &n);
while (i++ < nVerts)
{
    fscanf(fPtr, "%*s %f %f %f", &x, &y, &z);
    float* coords = new float[3];
    coords[0] = x;
    coords[1] = y;
    coords[2] = z;
  //  cout<<"x "<<x<<" y"<<y<<" z"<<z<<std::endl;
    addVertex(coords);
}
    cout<<"i :"<<i<<std::endl;
while (fscanf(fPtr, "%d", &i) != EOF)
{
    fscanf(fPtr, "%*s %f %f %f", &x, &y, &z);
    
    addTriangle((int)x, (int)y, (int)z);
}
    cout<<" tris: "<<tris.size()<<" verts: "<<verts.size()<<" edges: "<<edges.size()<<std::endl;
fclose(fPtr);

}

int Mesh::addVertex(float* coords )
{
    int idx ;
    if (verts.size() == 0)
        idx = 0;
    else
        idx = (int) verts[verts.size()-1]->idx + 1;
    //float* c = new float[3];
    //c[0] = x;
    //c[1] = y;
    //c[2] = z;
    
    verts.push_back( new Vertex(idx, coords) );
    return idx;

}


void Mesh::addTriangle(int v1, int v2, int v3)
{
    
    int idx = tris.size();
    
    
    
    //cout<<s.x<<" "<<s.y<<" "<<s.z<<std::endl;
    //  cout<<v1<<" "<<v2<<" "<<v3<<std::endl;
    
    tris.push_back(new Triangle(idx, v1, v2, v3));
    
    
    //set up structre
    
    verts[v1]->triList.push_back(idx);
    verts[v2]->triList.push_back(idx);
    verts[v3]->triList.push_back(idx);
    
    if (!makeVertsNeighbor(v1, v2))
        addEdge(v1, v2);
    
    if (!makeVertsNeighbor(v1, v3))
        addEdge(v1, v3);
    
    if (!makeVertsNeighbor(v2, v3))
        addEdge(v2, v3);
    
}



bool Mesh::makeVertsNeighbor(int v1i, int v2i)
{
    //returns true if v1i already neighbor w/ v2i; false o/w
    
    for (int i = 0; i < verts[v1i]->vertList.size(); i++)
        if (verts[v1i]->vertList[i] == v2i)
        {return true;}
    
    verts[v1i]->vertList.push_back(v2i);
    verts[v2i]->vertList.push_back(v1i);
    return false;
}


void Mesh::addEdge(int v1, int v2)
{
    
    
    int idx = edges.size();
    
    edges.push_back(new Edge(idx, v1, v2,distanceBetween(verts[v1]->coords, verts[v2]->coords)));
    // cout<<" idx:"<<idx<<" "<<v1<<" "<<v2<<std::endl;;
    
    verts[v1]->edgeList.push_back(idx);
    verts[v2]->edgeList.push_back(idx);
    
}
void Mesh::FindHoles(){
    
    for(int a=0;a<edges.size();a++){

        if(isBoundary(verts[edges[a]->v1i], verts[edges[a]->v2i])){
                
        }
    }
}
bool Mesh::isBoundary(Vertex *v1 , Vertex *v2)
{
    int counter = 0;
    for(int i = 0 ; i < v1->triList.size() && counter < 2; i++)
    {
        for(int j = 0 ; j < v2->triList.size() ; j++)
        {
            if(v2->triList[j] == v1->triList[i])
            {
                counter++;
                break;
            }
        }
    }
    return (counter == 1);
}

///////////////
bool Mesh::triangleExists(int v1i, int v2i, int v3i) {
    int idx = -1;
    for (int i = 0; i < tris.size(); i++) {
        if (tris[i]->v1i == v1i && tris[i]->v2i == v2i && tris[i]->v3i == v3i) {
            idx = tris[i]->idx;
        }
    }
    return idx != -1;
}
void Mesh::removeTriangle(int v1i, int v2i, int v3i)
{
    int idx = -1;
    for (int i = 0; i < tris.size(); i++) {
        if (tris[i]->v1i == v1i && tris[i]->v2i == v2i && tris[i]->v3i == v3i) {
            idx = tris[i]->idx;
            tris.erase(tris.begin() + i);
        }
    }
    
    if (idx == -1) {
        cout << "no such triangle " << endl;
        return;
    }
    
    for (int i = 0; i < verts[v1i]->triList.size(); i++) {
        if (idx == verts[v1i]->triList[i]) {
            verts[v1i]->triList.erase(verts[v1i]->triList.begin() + i);
        }
    }
    for (int i = 0; i < verts[v2i]->triList.size(); i++) {
        if (idx == verts[v2i]->triList[i]) {
            verts[v2i]->triList.erase(verts[v2i]->triList.begin() + i);
        }
    }
    for (int i = 0; i < verts[v3i]->triList.size(); i++) {
        if (idx == verts[v3i]->triList[i]) {
            verts[v3i]->triList.erase(verts[v3i]->triList.begin() + i);
        }
    }
    
    if (!makeVertsUnneighbors(v1i, v2i))
        removeEdge(v1i, v2i);
    
    if (!makeVertsUnneighbors(v1i, v3i))
        removeEdge(v1i, v3i);
    
    if (!makeVertsUnneighbors(v2i, v3i))
        removeEdge(v2i, v3i);
}

void Mesh::splitTriangle(int idx) {
    Triangle *tri = tris[10];
    
    float coord_centroid[3] = {
        (verts[tri->v1i]->coords[0] + verts[tri->v2i]->coords[0] + verts[tri->v3i]->coords[0]) / 3,
        (verts[tri->v1i]->coords[1] + verts[tri->v2i]->coords[1] + verts[tri->v3i]->coords[1]) / 3,
        (verts[tri->v1i]->coords[2] + verts[tri->v2i]->coords[2] + verts[tri->v3i]->coords[2]) / 3 };
    
    int idx_centroid = addVertex(coord_centroid);
    
    cout << coord_centroid[0] << " " << coord_centroid[1] << " " << coord_centroid[2] << " " << idx_centroid << endl;
    
    addTriangle(verts[tri->v3i]->idx, verts[tri->v1i]->idx, idx_centroid);
    addTriangle(verts[tri->v2i]->idx, verts[tri->v3i]->idx, idx_centroid);
    addTriangle(verts[tri->v1i]->idx, verts[tri->v2i]->idx, idx_centroid);
    
    removeTriangle(verts[tri->v1i]->idx, verts[tri->v2i]->idx, verts[tri->v3i]->idx);
}
bool Mesh::makeVertsUnneighbors(int v, int w)
{
    //try to make v and w unneighbors; return true if not neigbors
    
    for (int check = 0; check < (int)verts[v]->vertList.size(); check++)
        if (verts[v]->vertList[check] == w) {
            verts[v]->vertList.erase(verts[v]->vertList.begin() + check);
        }
    
    for (int check = 0; check < (int)verts[w]->vertList.size(); check++)
        if (verts[w]->vertList[check] == v) {
            verts[w]->vertList.erase(verts[w]->vertList.begin() + check);
            return false;
        }
    
    return true;
}
float Mesh::distanceBetween(float* a, float* b)
{
    return sqrt( (a[0]-b[0])*(a[0]-b[0]) + (a[1]-b[1])*(a[1]-b[1]) + (a[2]-b[2])*(a[2]-b[2]));
}
void Mesh::removeEdge(int a, int b)
{
    int idx = -1;
    for (int i = 0; i < edges.size(); i++) {
        if ((edges[i]->v1i == a && edges[i]->v2i == b) || (edges[i]->v1i == b && edges[i]->v2i == a)) {
            idx = edges[i]->idx;
            edges.erase(edges.begin() + i);
        }
    }
    if (idx == -1)
        return;
    
    for (int i = 0; i < verts[a]->edgeList.size(); i++) {
        if (verts[a]->edgeList[i] == idx)
            verts[a]->edgeList.erase(verts[a]->edgeList.begin() + i);
    }
    for (int i = 0; i < verts[b]->edgeList.size(); i++) {
        if (verts[b]->edgeList[i] == idx)
            verts[b]->edgeList.erase(verts[b]->edgeList.begin() + i);
    }
}


