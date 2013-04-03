//
//  engin.h
//  MyCCraft
//
//  Created by WaWa-YoDa on 28/03/13.
//  Copyright (c) 2013 WaWa-YoDa. All rights reserved.
//

#ifndef __MyCCraft__engin__
#define __MyCCraft__engin__

#include <iostream>
#include "openGLSetup.h"
#include <vector>
#include "bloc.h"

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#ifdef __WINDOWS__
#include <WinBase.h>
#else
#include <unistd.h>
#endif


#include <pthread.h>
#include "openGLSetup.h"

#if defined(__cplusplus)
extern "C"
#endif

using namespace std;

typedef unsigned char   Bool;

class engine{
    
    
public:
    float angleVision = -3.14/2.5;
    float positionX = -5, positionY = 6, positionZ = 16;
    float visionX = 0, visionY = 0, visionZ = 0;
    float vitesse = 1.0;
    class OpenGLSetup* session;
    int state = 1;
    
    
    vector<bloc*> listBloc;
    
    void setSession(class OpenGLSetup* aSession);
    void start();
    static void* run(void*);
    
    void perform(Bool* key,Bool* keyUp,Bool* keyDown);
    void loadMap(string fileName);
    



    
};

#endif /* defined(__MyCCraft__engin__) */
