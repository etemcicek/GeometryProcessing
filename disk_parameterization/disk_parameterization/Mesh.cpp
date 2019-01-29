//
//  Mesh.cpp
//  disk_parameterization
//
//  Created by Ethem Bilgehan CICEK on 15.12.2018.
//  Copyright © 2018 Ethem Bilgehan CICEK. All rights reserved.
//





#include "Mesh.hpp"
#include<iostream>
#include <stdio.h>
#include <limits>
#include<vector>
#include <iomanip>
#include <cmath>
#include <utility>
#include</Users/ethembilgehancicek/Desktop/C++/MeshGenerate/include_fade2d/Fade_2D.h>
#include</Users/ethembilgehancicek/Desktop/C++/MeshGenerate/include_fade2d/Point2.h>
#include <algorithm>
#include<//opt/local/include/eigen3/eigen/core>
#include<//opt/local/include/eigen3/eigen/Cholesky>



#define PI 3.14159265
using namespace std;

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
void Mesh::addVertex(float x, float y, float z)
{
    int idx =verts.size();
    float a=0,b=0,c=0;
    
    a=x/(1-z);
    b=y/(1-z);
    verts.push_back(new Vertex( idx,x,y,z));
    
}

void Mesh::addEdge(int v1, int v2)
{
    
    
    int idx = edges.size();
    
    edges.push_back(new Edge(idx, v1, v2));
    
    verts[v1]->edgeList.push_back(idx);
    verts[v2]->edgeList.push_back(idx);
    
}





void Mesh::FindBorder(){
    int counterr=0;
    
    cout<<" ----Find Borders----"<<" \n";
    for(int x=0;x<edges.size();x++){
        for(int y=0;y<tris.size();y++){
            
            
            if(( (edges[x]->v1i)==(tris[y]->v1i)&&(edges[x]->v2i)==(tris[y]->v2i) ) ){
                counterr++;
            }
            
            if( ( (edges[x]->v1i)==(tris[y]->v1i)&&(edges[x]->v2i)==(tris[y]->v3i) )){
                counterr++;
            }
            if( ( (edges[x]->v1i)==(tris[y]->v2i)&&(edges[x]->v2i)==(tris[y]->v3i) ) ){
                counterr++;
            }
            if( ( (edges[x]->v1i)==(tris[y]->v2i)&&(edges[x]->v2i)==(tris[y]->v1i) )  ){
                counterr++;
            }
            if( ( (edges[x]->v1i)==(tris[y]->v3i)&&(edges[x]->v2i)==(tris[y]->v2i) )  ){
                counterr++;
            }
            if( ( (edges[x]->v1i)==(tris[y]->v3i)&&(edges[x]->v2i)==(tris[y]->v1i) )  ){
                counterr++;
            }
            
        }
        if(counterr==1){
            borders.push_back(new Edge(edges[x]->v1i,edges[x]->v2i));
            
        }
        counterr=0;
    }
    
    cout<<"Borders size: "<<borders.size()<<std::endl;
    std::vector< pair<float, float> > vec;
    
    
    
    std::vector<int> x1;
    std::vector<int> x2;
    

    
    
    
    
    
    for(int x=0;x<borders.size();x++){
        if(  (verts[borders[x]->v1i]->y>=0 && verts[borders[x]->v2i]->y>=0)  ){
      
            x1.push_back(borders[x]->v1i);
            x1.push_back(borders[x]->v2i);
            
            
        }
    }
    for(int x=0;x<borders.size();x++){
        if(  ( (verts[borders[x]->v1i]->y<=0) && (verts[borders[x]->v2i]->y<=0 ) ) ||  ( borders[x]->v1i==1890 && borders[x]->v2i==1860   )  ){
            
          
            x2.push_back(borders[x]->v1i);
            x2.push_back(borders[x]->v2i);
        }
    }
   
    
  
    for(int a=0;a<x1.size();a++){
        for(int b=a+1;b<x1.size();b++){
            if(x1[a]==x1[b] ){
                x1.erase(x1.begin()+b);
            }
            
        }
    }

    
    cout<<std::endl;
    for(int a=0;a<x2.size();a++){
        for(int b=a+1;b<x2.size();b++){
            if(x2[a]==x2[b] ){
                x2.erase(x2.begin()+b);
            }
            
        }
    }
    x2.erase(x2.begin()+1);

    
    for(int a=0;a<x1.size();a++)
        bordersInto.push_back(x1[a]);
    for(int b=0;b<x2.size();b++)
        bordersInto.push_back(x2[b]);
    std::vector< pair<float, float> > sortedy;
    std::vector< pair<float, float> > sortedx;
    

    
    for(int a=0;a<x1.size();a++){
        
        sortedx.push_back(make_pair(verts[x1[a]]->x, verts[x1[a]]->y));
    }
    
    for(int a=0;a<x2.size();a++){
        
        sortedy.push_back(make_pair(verts[x2[a]]->x, verts[x2[a]]->y));
        
    }
    
    
    
    std::sort(sortedx.begin(),sortedx.end());
    std::sort(sortedx.begin(),sortedx.end());

    std::sort(sortedy.begin(),sortedy.end());

    cout<<std::endl;
    
    std::vector< pair<float, float> > result;
    for(int x=sortedx.size()-1;x>=0;x--)
        result.push_back(make_pair(sortedx[x].first, sortedx[x].second));
    for(int y=0;y<sortedy.size();y++)
        result.push_back(make_pair(sortedy[y].first, sortedy[y].second));
    
  
    
    
    
    double (*T)[2] = new double[result.size()][2];
    int b=0;
    double deg=0;
    float increment=360/result.size();
std:setprecision(6);

    for(int x=0;x<result.size();x++){
      //  cout<<" index: "<<x<<" deg: "<<deg<<" cos : "<<cos(deg*PI/180)*0.5<<" sin: "<<sin(deg*PI/180)*0.5<<std::endl;
        T[b][0]=cos(deg*PI/180)*0.5;
        T[b][1]=sin(deg*PI/180)*0.5;
        
        for(int y1=0;y1<verts.size();y1++){
            if(result[x].first==verts[y1]->x && result[x].second==verts[y1]->y){
                verts[y1]->x=T[b][0];
                verts[y1]->y=T[b][1];
                
            }
        }
        deg=deg + 1.4574;
        b++;
    }
    cout<<" ----Done----"<<std::endl;
    
    cout<<"----Laplacian Matrix Multiplication----"<<std::endl;
    cout<<"Wait for a minute..."<<std::endl;

    
    
}

void Mesh::MatrixMultip(){
    using namespace Eigen;
    
    MatrixXf A(verts.size(),verts.size());
    VectorXf bx(verts.size());
    VectorXf by(verts.size());
    for(int x=0;x<verts.size();x++){
        for(int y=0;y<verts.size();y++){
            for(int z=0;z<verts[x]->vertList.size();z++){
                if(y==verts[x]->vertList[z]){
                    A(x,y)=1;
                    
                }
            }
                if(x==y){
                    signed int tmp=0;
                    tmp=(verts[x]->vertList.size())*-1;
                    A(x,y)=tmp;

                }
        }
    }

    for(int x=0;x<bordersInto.size();x++){
        for(int y=0;y<verts.size();y++){
            if(y==bordersInto[x]){
                A(bordersInto[x],y)=1;
            }
            else A(bordersInto[x],y)=0;
            
        }
    }
    for(int a=0;a<verts.size();a++){
        bx(a)=0; by(a)=0;}
    for(int a=0;a<verts.size();a++){
        for(int b=0;b<verts.size();b++){
            if(a==bordersInto[b]){
                bx(a)=verts[a]->x;
                by(a)=verts[a]->y;
            }
        }
            
    }

    VectorXf bxRes;
    VectorXf byRes;

    bxRes=(A.transpose() * A).ldlt().solve(A.transpose() * bx);
    byRes=(A.transpose() * A).ldlt().solve(A.transpose() * by);

       for(int b=0;b<verts.size();b++)
        cout<<"bx: "<<bxRes(b)<<" by: "<<byRes(b)<<std::endl;
    for(int a=0;a<verts.size();a++)
    {
        cout<<"index:"<<a;

        for(int b=0;b<verts.size();b++){
            cout<<" - "<<A(a,b);}
        
        cout<<std::endl;
    }
    for(int x=0;x<verts.size();x++){
        verts[x]->x=bxRes(x);
        verts[x]->y=byRes(x);

    }
    
    Draw();
    
}
void Mesh::Draw(){
    using namespace GEOM_FADE2D;
    double (*S)[6] = new double[tris.size()][6];
    for(int i=0;i<tris.size();i++){
        S[i][0]=verts[tris[i]->v1i]->x;
        S[i][1]=verts[tris[i]->v1i]->y;
        
        
        S[i][2]=verts[tris[i]->v2i]->x;
        S[i][3]=verts[tris[i]->v2i]->y;
        
        
        S[i][4]=verts[tris[i]->v3i]->x;
        S[i][5]=verts[tris[i]->v3i]->y;
        
        
    }
    
    std::vector<Point2> vPoints;
    for(int a=0;a<tris.size();a++){
        for(int b=0;b<6;b=b+2){
            vPoints.push_back(Point2(S[a][b],S[a][b+1]));
            
        }
        
        
        
    }
    
    
    Fade_2D* dt1=new Fade_2D();
    dt1->insert(vPoints);
    dt1->show("/users/ethembilgehancicek/desktop/sotry1.ps");
    delete dt1;
}
