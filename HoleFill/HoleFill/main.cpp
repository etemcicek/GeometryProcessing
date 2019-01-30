//
//  main.cpp
//  HoleFill
//
//  Created by Ethem Bilgehan CICEK on 4.01.2019.
//  Copyright © 2019 Ethem Bilgehan CICEK. All rights reserved.
//
#include </opt/local/Library/Frameworks/Inventor.framework/Versions/C/Headers/Qt/SoQt.h>
#include </opt/local/Library/Frameworks/Inventor.framework/Versions/C/Headers/Qt/viewers/SoQtExaminerViewer.h>
//#include </opt/local/Library/Frameworks/SoQt.framework/Versions/A/Headers/viewers/SoqtExaminerViewer.h>
#include </opt/local/Library/Frameworks/Inventor.framework/Versions/C/Headers/nodes/SoSeparator.h>
#include <iostream>
#include "Mesh.hpp"
#include "Painter.hpp"
#include "HoleFiller.hpp"

int main(int argc, const char * argv[]) {
  
    QWidget * mainwin= SoQt::init(argv[0]);
    
    SoQtExaminerViewer * viewer = new SoQtExaminerViewer(mainwin);
    
    //make a dead simple scene graph by using the Coin library, only containing a single cone under the scenegraph root
    SoSeparator * root = new SoSeparator;
    root->ref();
    SoSeparator* generalShape = new SoSeparator();

    int question = 4;
    char* filename = "/users/ethembilgehancicek/downloads/bunny-hole.obj";
    
    Mesh * m = new Mesh();
    m->loadOff(filename);
    HoleFiller hfill(*m);
    hfill.fillHoles();
    
   // m->FindHoles();
    
    
    Painter* painter = new Painter();
    generalShape = painter->getShapeSep(m);
    
    root->addChild(generalShape);
    
    viewer->setSize(SbVec2s(640, 480));
    viewer->setSceneGraph(root);
    viewer->show();
    
    SoQt::show(mainwin);
    SoQt::mainLoop();
    delete viewer;
    root->unref();
    return 0;
}
