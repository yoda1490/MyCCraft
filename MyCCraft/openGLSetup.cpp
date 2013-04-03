//
//  OpenGLSetup.cpp
//  MyCCraft
//
//  Created by WaWa-YoDa on 28/03/13.
//  Copyright (c) 2013 WaWa-YoDa. All rights reserved.
//

#include "OpenGLSetup.h"


static OpenGLSetup* currentInstance;
    

OpenGLSetup::OpenGLSetup(string aWindowName, scene* aScene, int aWidth, int aHeight, engine* engine){
    windowName = aWindowName;
    theScene = aScene;
    width = aWidth;
    height = aHeight;
    theEngine = engine;
}

void OpenGLSetup::drawSceneCallback(){
    
    currentInstance->theScene->drawScene();
    currentInstance->resetKeyboardInput();
}

void OpenGLSetup::idle(void)
{
    glutPostRedisplay();
}

    
void OpenGLSetup::setupWindow(int *argcp, char **argv){
        printInteraction();
        glutInit(argcp, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        glutInitWindowSize(width, height);
        glutInitWindowPosition(100, 100);
        glutCreateWindow(windowName.c_str());
    
        currentInstance = this;
        glutDisplayFunc(OpenGLSetup::drawSceneCallback);
        glutReshapeFunc(resize);
        glutIdleFunc(OpenGLSetup::idle);
        glutKeyboardFunc(keyboard);
        glutKeyboardUpFunc(keyboardUp);
        glutSpecialFunc(keyboardSpecial);
        glutSpecialUpFunc(keyboardSpecialUp);
        glutMainLoop();
    }
    

    
    void OpenGLSetup::setupMouse(){
        
    }
    
    
    void OpenGLSetup::setupSpecialKeyBoard(int key, int x, int y){
        /**if (key == GLUT_KEY_DOWN){ positionX -= (vitesse * 1.5)*cos(angleVision) ;  positionZ -= (vitesse * 1.5)*sin(angleVision) ;}
        if( key == GLUT_KEY_UP){ positionX += ( vitesse * 1.5)*cos(angleVision) ;  positionZ += (vitesse * 1.5)*sin(angleVision) ;}
        if (key == GLUT_KEY_LEFT){ angleVision -= 0.05*(vitesse/2);}
        if( key == GLUT_KEY_RIGHT){ angleVision += 0.05*(vitesse/2);}
        if (key == GLUT_KEY_PAGE_DOWN){ positionY -= 0.5*(vitesse/2);}
        if( key == GLUT_KEY_PAGE_UP){ positionY += 0.5*(vitesse/2);}
        **/
        glutPostRedisplay();
        
    }
    
    // OpenGL window reshape routine.
     void OpenGLSetup::resize(int w, int h)
    {
        glViewport(0, 0, (GLsizei)w, (GLsizei)h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(60.0, (float)w/(float)h, 1.0, 100.0);
        glMatrixMode(GL_MODELVIEW);
    }

void OpenGLSetup::printInteraction(){
    cout << "Interraction: " << endl;
}

 
 
 Bool* OpenGLSetup::getKeys(){
 return key;
 }
 
 Bool* OpenGLSetup::getKeysUp(){
 return keyUp;
 }
 Bool* OpenGLSetup::getKeysDown(){
 return keyDown;
 }
 
 void OpenGLSetup::resetKeyboardInput(void)
 {
 int        i;
 
 for (i = 0; i < NUM_KEY_CODES; i++)
 {
 keyDown[i] = false;
 keyUp[i] = false;
 }
 }
 
 void OpenGLSetup::keyboard(unsigned char rawKeyCode, int x, int y)
 {
 if (rawKeyCode < NUM_KEY_CODES)
 {
 currentInstance->key[rawKeyCode] = true;
 currentInstance->keyDown[rawKeyCode] = true;
 }
 }
 
 void OpenGLSetup::keyboardUp(unsigned char rawKeyCode, int x, int y)
 {
 if (rawKeyCode < NUM_KEY_CODES)
 {
 currentInstance->key[rawKeyCode] = false;
 currentInstance->keyUp[rawKeyCode] = false;
 }
 }
 
 void OpenGLSetup::keyboardSpecial(int rawKeyCode, int x, int y)
 {
 switch (rawKeyCode)
 {
 case GLUT_KEY_LEFT:
 currentInstance->key[LEFT_ARROW] = true;
 currentInstance->keyDown[LEFT_ARROW] = true;
 break;
 case GLUT_KEY_UP:
 currentInstance->key[UP_ARROW] = true;
 currentInstance->keyDown[UP_ARROW] = true;
 break;
 case GLUT_KEY_RIGHT:
 currentInstance->key[RIGHT_ARROW] = true;
 currentInstance->keyDown[RIGHT_ARROW] = true;
 break;
 case GLUT_KEY_DOWN:
 currentInstance->key[DOWN_ARROW] = true;
 currentInstance->keyDown[DOWN_ARROW] = true;
 break;
 }
 }
 
 void OpenGLSetup::keyboardSpecialUp(int rawKeyCode, int x, int y)
 {
 switch (rawKeyCode)
 {
 case GLUT_KEY_LEFT:
 currentInstance->key[LEFT_ARROW] = false;
 currentInstance->keyUp[LEFT_ARROW] = true;
 break;
 case GLUT_KEY_UP:
 currentInstance->key[UP_ARROW] = false;
 currentInstance->keyUp[UP_ARROW] = true;
 break;
 case GLUT_KEY_RIGHT:
 currentInstance->key[RIGHT_ARROW] = false;
 currentInstance->keyUp[RIGHT_ARROW] = true;
 break;
 case GLUT_KEY_DOWN:
 currentInstance->key[DOWN_ARROW] = false;
 currentInstance->keyUp[DOWN_ARROW] = true;
 break;
 }
 }
