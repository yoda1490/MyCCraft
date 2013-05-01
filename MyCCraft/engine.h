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
#include "scene.h"
#include <vector>
#include "bloc.h"
#include <pthread.h>
#include "openGLSetup.h"
#include "perso.h"
#include "collision.h"
#include <cmath>
#include <map>


#include "chunk.h"
#include "field.h"

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#ifdef _WIN32
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
	static const int fps=60;
    static const int visibility = 32; //the visibility of the player
    static const int visibilitySelect = 16;
    
    perso player;
    float futurX, futurY, futurZ;
    float visionX, visionY, visionZ;
    
    float godX, godY, godZ;
    
    float gravity;
    
    float vitesse;
    class OpenGLSetup* session;
    class scene* scene;
    int state;
    
    int viewMode; //0=FPS 1=fixed on 0:20:0 2=camera follow
    bool viewModePressed; //to only change one time until touche is relached
    bool changeBlocPressed; //same but for changing bloc in player inventory
    
    bool contextInitialized;//display and other things
    
    bool keyboardInitialized;
    bool mouseLeftClicked;
    bool mouseRightClicked;
    int  mouseX;
    int  mouseY;
    unsigned int lastLeftClic;
    unsigned int lastRightClic;
    unsigned int reloadTime;
    
    
    bool isSelecting; //selection picking mode
    
    
    int selectedBlocNumber;
    map<int, bloc*> pickedBloc;
    int counterPicked;
    bloc* selectedBloc;
    int selectedFace;
    
    int centerX;
    int centerY;
    
    int centerMouse;
    static const int maxCenterMouse = 200;
    

     
    field* aField;
    
    engine();
    void setSession(class OpenGLSetup* aSession);
    void setScene(class scene* aScene);
    void start();
    static void* run(void*);
    
    void perform(Bool* key,Bool* keyUp,Bool* keyDown);
    void simplePerform(Bool* key,Bool* keyUp,Bool* keyDown); //no collision detecttion, no action juste moves
    void loadfield(string fileName);
    

    



    
};

#endif /* defined(__MyCCraft__engin__) */
