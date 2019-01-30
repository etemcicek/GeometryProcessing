//
//  Mesh.cpp
//  dijkstra
//
//  Created by Ethem Bilgehan CICEK on 7.12.2018.
//  Copyright © 2018 Ethem Bilgehan CICEK. All rights reserved.
//
#define _CRT_SECURE_NO_WARNINGS
#include "Mesh.hpp"

#include <queue>
#include <list>
#include <fstream>
#include<math.h>
using namespace std;
void Mesh::loadOff(const char* name)
{
    FILE* fPtr = fopen(name, "r");
    char str[334];
    
    fscanf(fPtr, "%s", str);
    
    int nVerts, nTris, n, i = 0;
    float x, y, z;
    
    fscanf(fPtr, "%d %d %d\n", &nVerts, &nTris, &n);
    while (i++ < nVerts)
    {
        fscanf(fPtr, "%f %f %f", &x, &y, &z);
        addVertex(x, y, z);
    }
    
    while (fscanf(fPtr, "%d", &i) != EOF)
    {
        fscanf(fPtr, "%f %f %f", &x, &y, &z);
        addTriangle((int)x, (int)y, (int)z);
    }
    
    fclose(fPtr);
}

void Mesh::addTriangle(int v1, int v2, int v3)
{
    int idx = tris.size();
    tris.push_back(new Triangle(idx, v1, v2, v3));
    
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
    for (int i = 0; i < verts[v1i]->vertList.size(); i++)
        if (verts[v1i]->vertList[i] == v2i)
            return true;
    
    verts[v1i]->vertList.push_back(v2i);
    verts[v2i]->vertList.push_back(v1i);
    return false;
}

void Mesh::addVertex(float x, float y, float z)
{
    int idx = verts.size();
    float* c = new float[3];
    c[0] = x;
    c[1] = y;
    c[2] = z;
    
    verts.push_back(new Vertex(idx, c));
}

void Mesh::addEdge(int v1, int v2)
{
    int idx = edges.size();
    
    float x = verts[v1]->coords[0] - verts[v2]->coords[0];
    float y = verts[v1]->coords[1] - verts[v2]->coords[1];
    float z = verts[v1]->coords[2] - verts[v2]->coords[2];
    float d = sqrt(x*x + y*y + z*z);
    
    edges.push_back(new Edge(idx, v1, v2, d));
    
    verts[v1]->edgeList.push_back(idx);
    verts[v2]->edgeList.push_back(idx);
}

vector< int > Mesh::ShortestPath(int src, bool print)
{
    vector< float > distance(verts.size(), numeric_limits<float>::infinity());
    vector< int > closest(verts.size());
    
    
    
    priority_queue< pair< float, int >, vector< pair< float, int > >, greater< pair< float, int > > > pq;
    pq.push(make_pair(0.0f, src));
    distance[src] = 0.0f;
    closest[src] = -1;
    
    while (!pq.empty())
    {
        int u = pq.top().second;
        
        pq.pop();
        
        vector< int >::iterator i;
        for (i = verts[u]->vertList.begin(); i != verts[u]->vertList.end(); ++i)
        {
            int v = *i;
            float weight = sqrt(pow(verts[u]->coords[0] - verts[v]->coords[0], 2) + pow(verts[u]->coords[1] - verts[v]->coords[1], 2) + pow(verts[u]->coords[2] - verts[v]->coords[2], 2));
            
            if (distance[v] > distance[u] + weight)
            {
                distance[v] = distance[u] + weight;
                pq.push(make_pair(distance[v], v));
                
                closest[v] = u;
            }
        }
    }
    
    if (print)
    {
        std::ofstream output("/users/ethembilgehancicek/desktop/c++/dijkstra/Geo.txt");
        if(output.is_open()){
        for (int i = 0; i < verts.size(); i++) {
            if (i == (verts.size() - 1))
                output << distance[i] << "\n";
            else
                output << distance[i] << " ";
        }
            
            
        }
        output.close();
    }
    
    return closest;
}

vector< int > Mesh::getShortestPath(vector< int > &output, vector< int > pathList, int dest)
{
    output.push_back(dest);
    
    if (pathList[dest] == -1)
        return output;
    
    getShortestPath(output, pathList, pathList[dest]);
    
    return output;
}

void Mesh::printGeoMatrix()
{
    remove("./outputs/Geo.txt");
    for (int i = 0; i < verts.size(); i++)
    {
        ShortestPath(i, true);
    }
}
