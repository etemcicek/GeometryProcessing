//
//  main.cpp
//  dijkstra
//
//  Created by Ethem Bilgehan CICEK on 7.12.2018.
//  Copyright © 2018 Ethem Bilgehan CICEK. All rights reserved.
#include "Mesh.hpp"
#include "Painter.hpp"


#include </opt/local/Library/Frameworks/Inventor.framework/Headers/Qt/SoQt.h>
#include </opt/local/Library/Frameworks/Inventor.framework/Headers/Qt/viewers/SoQtExaminerViewer.h>
//#include </opt/local/Library/Frameworks/SoQt.framework/Versions/A/Headers/viewers/SoqtExaminerViewer.h>
#include </opt/local/Library/Frameworks/Inventor.framework/Headers/nodes/SoSeparator.h>
#include </opt/local/Library/Frameworks/Inventor.framework/Headers/nodes/SoCone.h>

using namespace std;





int main(int, char ** argv)
{
       QWidget * mainwin= SoQt::init(argv[0]);
    
    // Create the scene
    SoQtExaminerViewer * viewer =new  SoQtExaminerViewer(mainwin);
    SoSeparator * root = new SoSeparator;
    root->ref();
    
    // Load the mesh
    Mesh* mesh = new Mesh();
    mesh->loadOff("/users/ethembilgehancicek/desktop/c++/meshes/man0.off");
    
    Vertex* v_src = mesh->verts[10];                      ////Source point
    Vertex* v_dest = mesh->verts[200];                    ////Destination point
    
    

    //mesh->printGeoMatrix();
    //cout << "Geodestic Printed to /outputs/geo.txt" << endl;

    
    vector< int > allPaths = mesh->ShortestPath(v_src->idx);                //shortest path calculation

    //find shortest path
    vector< int > path;
    mesh->getShortestPath(path, allPaths, v_dest->idx);
    
    //paint shortest path
    Painter* painter = new Painter();
    root->addChild(painter->getShapeSep(mesh, path));
    
    cout << "Dijkstra " << endl;

    
    // Create the viewer
    viewer->setSize(SbVec2s(800, 800));
    viewer->setSceneGraph(root);
    viewer->show();
    
    SoQt::show(mainwin);
    SoQt::mainLoop();
    delete viewer;
    root->unref();
    
    // PROGRAM_END
    return 0;
}
