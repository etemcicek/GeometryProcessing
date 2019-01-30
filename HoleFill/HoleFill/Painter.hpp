//
//  Painter.hpp
//  HoleFill
//
//  Created by Ethem Bilgehan CICEK on 4.01.2019.
//  Copyright © 2019 Ethem Bilgehan CICEK. All rights reserved.
//

#ifndef Painter_hpp
#define Painter_hpp

#include <stdio.h>

#include </opt/local/Library/Frameworks/Inventor.framework/Versions/C/Headers/nodes/SoSeparator.h>
//#include <Inventor/nodes/SoCube.h>
#include </opt/local/Library/Frameworks/Inventor.framework/Versions/C/Headers/nodes/SoMaterial.h>
#include </opt/local/Library/Frameworks/Inventor.framework/Versions/C/Headers/nodes/SoShapeHints.h>
#include </opt/local/Library/Frameworks/Inventor.framework/Versions/C/Headers/nodes/SoCoordinate3.h>
#include </opt/local/Library/Frameworks/Inventor.framework/Versions/C/Headers/nodes/SoIndexedFaceSet.h>
#include "Mesh.hpp"

class Painter
{
public:
    SoSeparator* getShapeSep(Mesh* mesh);
private:
    
};
#endif /* Painter_hpp */
