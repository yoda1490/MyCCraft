//
//  block.h
//  MyCCraft
//
//  Created by WaWa-YoDa on 28/03/13.
//  Copyright (c) 2013 WaWa-YoDa. All rights reserved.
//

#ifndef __MyCCraft__block__
#define __MyCCraft__block__

#include <iostream>
#include "string"

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif


using namespace std;

class bloc{
    
public:
    
    float diff = 0.1; // red and blue diffuse reflectance of the submarine monster
    float emi = 0.1; // red and blue emittance of the submarine monster
    
    float spec = 1.0; // White specular reflectance.
    float shi = 30.0; // Shininess.
    
    float position[3];
    float orient = 0;
    float size = 1;
    float color[4];
    string textureURL;
    
    bool visible = true;
    
    
    bloc(const bloc &source); //copy constructor
    bloc(int idBloc, float x, float y, float z, float orientation);
    bloc(float x, float y, float z,float orientation, float colorX, float colorY, float colorZ, float colorA);
    bloc(float x, float y, float z,float orientation, float colorX, float colorY, float colorZ, float colorA, float aSize);
    void draw();
    void light();
    
};

#endif /* defined(__MyCCraft__block__) */
