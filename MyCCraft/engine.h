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
#include <pthread.h>
#include "openGLSetup.h"
#include "perso.h"
#include "collision.h"
#include <cmath>

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




#if defined(__cplusplus)
extern "C"
#endif

using namespace std;

typedef unsigned char   Bool;

class engine{
    
    
public:
    perso player;
    float futurX=0, futurY=0, futurZ=0;
    float visionX = 0, visionY = 0, visionZ = 0;
    
    float godX=0, godY=10, godZ=0;
    
    float gravity = 15.0;
    
    float vitesse = 0.25;
    class OpenGLSetup* session;
    int state = 1;
    
    int viewMode = 0; //0=FPS 1=fixed on 0:20:0 2=camera follow
    bool viewModePressed = false; //to only change one time until touche is relached
    
    vector<bloc*> listBloc;
    
    void setSession(class OpenGLSetup* aSession);
    void start();
    static void* run(void*);
    
    void perform(Bool* key,Bool* keyUp,Bool* keyDown);
    void loadMap(string fileName);
    



    
};

#endif /* defined(__MyCCraft__engin__) */
