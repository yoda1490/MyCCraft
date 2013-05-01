//
//  scene.h
//  MyCCraft
//
//  Created by WaWa-YoDa on 28/03/13.
//  Copyright (c) 2013 WaWa-YoDa. All rights reserved.
//

#ifndef __MyCCraft__scene__
#define __MyCCraft__scene__

#include <iostream>
#include <cmath>
#include "engine.h"
#include "bloc.h"

#include "chunk.h"
#include "region.h"
#include "field.h"

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;

static float LIGHT0X = 0.0f, LIGHT0Y = 300.0f, LIGHT0Z = 0.0f;
static float QUADATT0 = 0.000009f; //quadratic attenuation light 0

class scene{
    
    bool initialized;
    
    //position of us

    class engine* eng;
    
public:
    scene(class engine* anEngine);
    void drawScene(bloc* detectFace=NULL);
    void setup();
    void lighting(void);
    
    
    //lighting
    //light position
    float light0X, light0Y, light0Z;
    
    float quadAtt0; //quadratic attenuation light 0
};

#endif /* defined(__MyCCraft__scene__) */


