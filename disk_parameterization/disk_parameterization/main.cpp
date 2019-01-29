//
//  main.cpp
//  disk_parameterization
//
//  Created by Ethem Bilgehan CICEK on 15.12.2018.
//  Copyright © 2018 Ethem Bilgehan CICEK. All rights reserved.
//



#include <iostream>
#include "Mesh.hpp"

#include <algorithm>

using namespace std;
int main(int argc, char *argv[]) {
    
    
    
    Mesh mesh;
    
    mesh.loadOff("/Users/ethembilgehancicek/Desktop/C++/disk_parameterization/facem.off");
    
    
    
    mesh.FindBorder();
    mesh.MatrixMultip();
    
    return 0;
}
