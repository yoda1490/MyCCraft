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
#include <cmath>
#include <fstream>

class chunk;

#ifdef __APPLE__
#  include <GLUT/glut.h>
#  include <OpenGL/glext.h>
#else
#  include <GL/glut.h>
#  include <GL/glext.h>
#endif




using namespace std;


class bloc{
    
public:
    
    float diff = 0.1; // red and blue diffuse reflectance of the submarine monster
    float emi = 0.1; // red and blue emittance of the submarine monster
    
    float spec = 0.0; // White specular reflectance.
    float shi = 30.0; // Shininess.
    
    float positionX=-1, positionY=-1, positionZ=-1;
    float orient = 0;
    float size = 1;
    float color[4];
    string textureURL;
    
    chunk* owner = NULL;
    
    bool initialized = false;
    
    bool visible = true;
    
    int idBloc = -1;
    
    
    bloc(const bloc &source); //copy constructor
    bloc(int idB, float x, float y, float z, float orientation);
    bloc(float x, float y, float z,float orientation, float colorX, float colorY, float colorZ, float colorA);
    bloc(float x, float y, float z,float orientation, float colorX, float colorY, float colorZ, float colorA, float aSize);
    virtual void draw(float time=0, bool picking=false);
    void light(float time=0);
    void setChunk(chunk* c);
    chunk* getChunk();
    float texturePoints[2][2][2] =
     {
     {{0.0, 0.0}, {0.0, 1.0}},
     {{1.0, 0.0}, {1, 1.0}}
     };
    
    static GLuint texture;
    
    

    
};

#endif /* defined(__MyCCraft__block__) */
