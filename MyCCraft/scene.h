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
#include "map.h"

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;

class scene{
    
    bool initialized = false;
    
    //position of us

    class engine* eng;
    
public:
    scene(class engine* anEngine);
    void drawScene();
    void setup();
    void lighting(void);
    
    
    //lighting
    //light position
    float light0X = 0.0, light0Y = 300.0, light0Z = 0.0;
    
    float quadAtt0 = 0.000009; //quadratic attenuation light 0
};

#endif /* defined(__MyCCraft__scene__) */


