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
#endif

using namespace std;

//defult parameters
static const float DIFF = 0.1f, EMI = 0.1f, SPEC = 0.0f, SHI = 30.0f;
static const int POSX=-1, POSY=-1, POSZ=-1, ORIENT=0, SIZEDEF=1, IDBLOC=-1;
static const bool INIT=false, VISIBLE=true; 

class bloc{

public:
    
    float diff; // red and blue diffuse reflectance of the submarine monster
    float emi; // red and blue emittance of the submarine monster
    
    float spec; // White specular reflectance.
    float shi; // Shininess.
    
    float positionX, positionY, positionZ;
    float orient;
    float size;
    float color[4];
    string textureURL;
    
    chunk* owner;
    
    bool initialized;
    
    bool visible;
    
    int idBloc; //0=air
    
    bloc();
    bloc(const bloc &source); //copy constructor
    bloc(int idB, float x, float y, float z, float orientation);
    bloc(float x, float y, float z,float orientation, float colorX, float colorY, float colorZ, float colorA);
    bloc(float x, float y, float z,float orientation, float colorX, float colorY, float colorZ, float colorA, float aSize);
    virtual void draw(float time=0, bool picking=false);
    void light(float time=0);
    void setChunk(chunk* c);
    chunk* getChunk();
    float texturePoints[2][2][2];
    
    static GLuint texture;
    
    

    
};

#endif /* defined(__MyCCraft__block__) */
