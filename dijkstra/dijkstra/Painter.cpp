//
//  Painter.cpp
//  Viewer
//
//  Created by Ethem Bilgehan CICEK on 2.12.2018.
//  Copyright © 2018 Ethem Bilgehan CICEK. All rights reserved.

#include "Painter.hpp"
#include "Mesh.hpp"

SoSeparator* Painter::getShapeSep(Mesh* mesh, vector<int>targetPath)
 {
     SoSeparator* res = new SoSeparator();
     
     //color
     SoMaterial* mat = new SoMaterial();
     mat->diffuseColor.setValue(1, 1, 0);
     
     if (targetPath.size() > 0)
     {
         SoSeparator* edgeSep = new SoSeparator();
         
         SoMaterial* edgeMat = new SoMaterial();
         edgeMat->diffuseColor.setValue(1, 0, 0);
         
         SoDrawStyle* edgeStyle = new SoDrawStyle;
         edgeStyle->lineWidth = 5.0f;
         edgeSep->addChild(edgeStyle);
         
         SoIndexedLineSet* ils = new SoIndexedLineSet;
         SoCoordinate3* co = new SoCoordinate3;
         
         for (unsigned int i = 0; i < targetPath.size() - 1; i++)
         {
             SbVec3f end1 = mesh->verts[targetPath[i]]->coords + SbVec3f(0.0f, 0.0f, 0.0f),
             end2 = mesh->verts[targetPath[i + 1]]->coords + SbVec3f(0.0f, 0.0f, 0.0f);
             co->point.set1Value(2 * i, end1);
             co->point.set1Value(2 * i + 1, end2);
         }
         
         for (unsigned int j = 0; j < targetPath.size() - 1; j++)
         {
             ils->coordIndex.set1Value(3 * j, 2 * j);
             ils->coordIndex.set1Value(3 * j + 1, 2 * j + 1);
             ils->coordIndex.set1Value(3 * j + 2, -1);
         }
         
         edgeSep->addChild(edgeMat);
         edgeSep->addChild(co);
         edgeSep->addChild(ils);
         

         SoSeparator* vertSep = new SoSeparator();
         
         SoMaterial* vertMat = new SoMaterial();
         vertMat->diffuseColor.setValue(1, 0, 1);
         vertSep->addChild(vertMat);
         
         SoDrawStyle* style = new SoDrawStyle;
         style->pointSize = 7.0f;
         vertSep->addChild(style);
         
         SoVertexProperty* vp = new SoVertexProperty;
         vp->vertex.set1Value(0, mesh->verts[targetPath[0]]->coords);
         vp->vertex.set1Value(1, mesh->verts[targetPath[targetPath.size() - 1]]->coords);
         
         SoPointSet* pSet = new SoPointSet;
         pSet->numPoints = 2;
         pSet->vertexProperty = vp;
         
         vertSep->addChild(pSet);

         res->addChild(edgeSep);
         res->addChild(vertSep);
     }
     
     //shape
     res->addChild(mat);
     
     SoCoordinate3* coords = new SoCoordinate3();
     for (int c = 0; c < mesh->verts.size(); c++)
         coords->point.set1Value(c, mesh->verts[c]->coords[0], mesh->verts[c]->coords[1], mesh->verts[c]->coords[2]);
     SoIndexedFaceSet* faceSet = new SoIndexedFaceSet();
     for (int c = 0; c < mesh->tris.size(); c++)
     {
         faceSet->coordIndex.set1Value(c * 4, mesh->tris[c]->v1i);
         faceSet->coordIndex.set1Value(c * 4 + 1, mesh->tris[c]->v2i);
         faceSet->coordIndex.set1Value(c * 4 + 2, mesh->tris[c]->v3i);
         faceSet->coordIndex.set1Value(c * 4 + 3, -1);
     }
     res->addChild(coords);
     res->addChild(faceSet);

 return res;
 }
