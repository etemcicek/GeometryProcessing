//
//  Painter.hpp
//  dijkstra
//
//  Created by Ethem Bilgehan CICEK on 7.12.2018.
//  Copyright © 2018 Ethem Bilgehan CICEK. All rights reserved.
//
#include"Mesh.hpp"
#ifndef Painter_hpp
#define Painter_hpp

#include <stdio.h>
#include </opt/local/Library/Frameworks/Inventor.framework/Versions/C/Headers/nodes/SoMaterial.h>
#include </opt/local/Library/Frameworks/Inventor.framework/Versions/C/Headers/nodes/SoCoordinate3.h>
#include </opt/local/Library/Frameworks/Inventor.framework/Versions/C/Headers/nodes/SoIndexedFaceSet.h>
#include </opt/local/Library/Frameworks/Inventor.framework/Versions/C/Headers/nodes/SoSeparator.h>
#include </opt/local/Library/Frameworks/Inventor.framework/Versions/C/Headers/nodes/SoShapeHints.h>
#include </opt/local/Library/Frameworks/Inventor.framework/Versions/C/Headers/nodes/SoIndexedLineSet.h>
#include </opt/local/Library/Frameworks/Inventor.framework/Versions/C/Headers/nodes/SoDrawStyle.h>
#include </opt/local/Library/Frameworks/Inventor.framework/Versions/C/Headers/nodes/SoPointSet.h>
#include </opt/local/Library/Frameworks/Inventor.framework/Versions/C/Headers/nodes/SoLineSet.h>
class Painter
{
public:
    SoSeparator* getShapeSep(Mesh* mesh, vector< int > targetPath);
};
#endif /* Painter_hpp */
