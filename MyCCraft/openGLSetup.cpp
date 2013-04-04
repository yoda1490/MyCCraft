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
    eng = engine;
}

void OpenGLSetup::drawSceneCallback(){
    
    currentInstance->resetKeyboardInput();
    
    currentInstance->theScene->drawScene();
    
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
    
        initKeyboardInput();
    
        currentInstance = this;
        glutDisplayFunc(OpenGLSetup::drawSceneCallback);
        glutReshapeFunc(resize);
        glutIdleFunc(OpenGLSetup::idle);
        glutKeyboardFunc(keyboard);
        glutKeyboardUpFunc(keyboardUp);
        glutSpecialFunc(keyboardSpecial);
        glutSpecialUpFunc(keyboardSpecialUp);
        glutMouseFunc(setupMouse);
        glutMotionFunc(setupMouseActiveMotion);
        glutPassiveMotionFunc(setupMousePassiveMotion);
    
        eng->contextInitialized = true;
    
        glutMainLoop();
    }
    

    
    void OpenGLSetup::setupMouse(int button, int state, int x, int y){
        
        currentInstance->eng->selectedBlock = currentInstance->pickFunction(x, y);
        
        
        if(button == 0){
            if (state == GLUT_DOWN){
                currentInstance->eng->mouseLeftClicked = true;
            }else{
                currentInstance->eng->mouseLeftClicked = false;
            }
        }
        if(button == 2){
            if (state == GLUT_DOWN){
                currentInstance->eng->mouseRightClicked = true;
            }else{
                currentInstance->eng->mouseRightClicked = false;
            }
        }
        
        currentInstance->eng->mouseX = x;
        currentInstance->eng->mouseY = y;
        
       
        
    }


    void OpenGLSetup::setupMouseActiveMotion(int x, int y) {
        currentInstance->eng->selectedBlock = currentInstance->pickFunction(x, y);
        currentInstance->eng->mouseX = x;
        currentInstance->eng->mouseY = y;
    }

    void OpenGLSetup::setupMousePassiveMotion(int x, int y) {
        currentInstance->eng->selectedBlock = currentInstance->pickFunction(x, y);
        currentInstance->eng->mouseLeftClicked = false;
        currentInstance->eng->mouseRightClicked = false;
        currentInstance->eng->mouseX = x;
        currentInstance->eng->mouseY = y;
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
        gluPerspective(60.0, (float)w/(float)h, 0.01, 100.0);
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


void OpenGLSetup::initKeyboardInput(void)
{
    int        i;
    
    for (i = 0; i < NUM_KEY_CODES+10; i++)
    {
        key[i] = false;
    }
    
    eng->keyboardInitialized = true;
}

 void OpenGLSetup::resetKeyboardInput(void)
 {
     int        i;
 
     for (i = 0; i < NUM_KEY_CODES+10; i++)
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



// The mouse callback routine.
unsigned int OpenGLSetup::pickFunction(int x, int y)
{
    int viewport[4]; // Viewport data.
    
    
    glGetIntegerv(GL_VIEWPORT, viewport); // Get viewport data.
    
    glSelectBuffer(1024, bufferPick); // Specify buffer to write hit records in selection mode
    (void) glRenderMode(GL_SELECT); // Enter selection mode.
    
    // Save the viewing volume defined in the resize routine.
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    
    // Define a viewing volume corresponding to selecting in 3 x 3 region around the cursor.
    glLoadIdentity();
    gluPickMatrix((float)x, (float)(viewport[3] - y), 3.0, 3.0, viewport);
    glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0); // Copied from the reshape routine.
    
    glMatrixMode(GL_MODELVIEW); // Return to modelview mode before drawing.
    glLoadIdentity();
    
    glInitNames(); // Initializes the name stack to empty.
    glPushName(0); // Puts name 0 on top of stack.
    
    // Determine hits by calling drawBallAndTorus() so that names are assigned.
    eng->isSelecting = true;
    theScene->drawScene();
    
    hits = glRenderMode(GL_RENDER); // Return to rendering mode, returning number of hits.
    
    // Restore viewing volume of the resize routine and return to modelview mode.
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    
    // Determine closest of the hit objects (if any).
    return findClosestHit(hits, bufferPick);
    
    //glutPostRedisplay();
    
}


// Process hit buffer to find record with smallest min-z value.
unsigned int OpenGLSetup::findClosestHit(int hits, unsigned int buffer[])
{
    unsigned int *ptr, minZ;
    
    minZ= 0xffffffff; // 2^32 - 1
    ptr = buffer;
    unsigned int closestName = 0;
    for (int i = 0; i < hits; i++)
    {
        ptr++;
        if (*ptr < minZ)
        {
            minZ = *ptr;
            ptr += 2;
            closestName = *ptr;
            ptr++;
        }
        else ptr += 3;
    }
    //if (closestName != 0) highlightFrames = 10;
    //cout <<  closestName << endl;
    return closestName;
}