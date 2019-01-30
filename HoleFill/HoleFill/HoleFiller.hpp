//
//  HoleFiller.hpp
//  HoleFill
//
//  Created by Ethem Bilgehan CICEK on 5.01.2019.
//  Copyright © 2019 Ethem Bilgehan CICEK. All rights reserved.
//

#ifndef HoleFiller_hpp
#define HoleFiller_hpp

#include <stdio.h>
#include "Mesh.hpp"

typedef vector<Vertex *> HoleVertices;
typedef vector<Edge *> HoleEdges;
typedef vector<Triangle *> HoleTriangles;

class HoleFiller
{
public:
    HoleFiller(Mesh & m);
    ~HoleFiller();
    void fillHoles();
    void identifyHoles();

private:
    void trianglulateHoles();
    void refine(int idx1 , int idx2 ,int idx3);

    void mesh_smooth();
    //identifyHoles
    bool isBoundary(Vertex *v1 , Vertex *v2);
    bool isChecked(Edge *edge);
    
    //trianglulateHoles
    float computeWeight(float* coordsV1, float* coordsV2, float* coordsV3);
    float computeArea(float* coordsV1, float* coordsV2, float* coordsV3);
    float computeDihedralAngle(float* coordsV1, float* coordsV2, float* coordsV3);
    void addToMesh( int hole_id , vector<vector<int>> &minimum_weight_index , int begin , int end );
    void UmbrellaOp();
private:
    vector<HoleVertices *> v_holes;
    vector<HoleEdges *> e_holes;
    vector<HoleTriangles *> t_holes;
    vector<int>ordered;
    Mesh *mesh;
};


#endif /* HoleFiller_hpp */
