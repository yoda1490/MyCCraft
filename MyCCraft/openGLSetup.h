//
//  OpenGLSetup.h
//  MyCCraft
//
//  Created by WaWa-YoDa on 28/03/13.
//  Copyright (c) 2013 WaWa-YoDa. All rights reserved.
//

#ifndef __MyCCraft__OpenGLSetup__
#define __MyCCraft__OpenGLSetup__

#include <iostream>
#include <string>
#include "scene.h"
#include "engine.h"

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;

typedef unsigned char   Bool;

typedef enum
{
    ENTER    = 3,
    TAB        = 9,
    RETURN    = 13,
    ESC        = 27,
    SPACE    = 32,
    DEL        = 127,
    UP_ARROW, DOWN_ARROW, LEFT_ARROW, RIGHT_ARROW,
    NUM_KEY_CODES
} KeyCode;

// Struct of bitmap file.
struct BitMapFile
{
    int sizeX;
    int sizeY;
    unsigned char *data;
};

class OpenGLSetup{

    string windowName = "";
    class scene* theScene ;
    int width, height;
    class engine * eng;
    
    
        
public:
    
    
    int hits; // Number of entries in hit buffer.
    
    
    OpenGLSetup(string windowName, scene* aScene, int width, int height,class engine* theEngine);
    static void drawSceneCallback();
    static void idle(void);
    void setupWindow(int *argcp, char **argv);
    static void setupKeyBoard(unsigned char key, int x, int y);
    static void setupMouse(int button, int state, int x, int y);
    static void setupMouseActiveMotion(int x, int y);
    static void setupSpecialKeyBoard(int key, int x, int y);
    static void setupMousePassiveMotion(int x, int y);
    static void resize(int w, int h);
    void printInteraction();
    void run();
    
    unsigned int pickFunction(int x, int y, bool face=false);
    unsigned int findClosestHit(int hits, unsigned int buffer[]);
    
    
    //keyboard
    
    Bool    key[NUM_KEY_CODES+10], keyDown[NUM_KEY_CODES+10], keyUp[NUM_KEY_CODES+10];
    Bool* getKeys();
    Bool* getKeysUp();
    Bool* getKeysDown();
    
    void initKeyboardInput(void);
    void resetKeyboardInput(void);
    static void keyboard(unsigned char rawKeyCode, int x, int y);
    
    
    
    static void keyboardUp(unsigned char rawKeyCode, int x, int y);
    static void keyboardSpecial(int rawKeyCode, int x, int y);
    static void keyboardSpecialUp(int rawKeyCode, int x, int y);
    
    
    
    
    int nbTexture=0;
    void loadExternalTextures(string path);
    BitMapFile* getBMPData(string filename);
};


#endif /* defined(__MyCCraft__OpenGLSetup__) */
