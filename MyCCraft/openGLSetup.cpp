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
        loadExternalTextures("/Users/WaWa-YoDa/polytech/AIT/OpenGL/MyCCraft/MyCCraft/textures/herb.bmp");
        glutMainLoop();
    }
    
        
    void OpenGLSetup::setupMouse(int button, int state, int x, int y){
        
        
        
        int id = currentInstance->pickFunction(x, y);
        currentInstance->eng->selectedBloc = id;
        
        
        if(button == 0){
            
            if (state == GLUT_DOWN){
                currentInstance->eng->mouseLeftClicked = true;
            }else{
                currentInstance->eng->mouseLeftClicked = false;
            }
        }
        if(button == 2){
             
            
            if (state == GLUT_DOWN){
                int idFace = currentInstance->pickFunction(x, y, true);
                if(idFace >0 && idFace <= 6) currentInstance->eng->selectedFace = idFace;
                currentInstance->eng->mouseRightClicked = true;
            }else{
                currentInstance->eng->mouseRightClicked = false;
            }
        }
        
        currentInstance->eng->mouseX = x;
        currentInstance->eng->mouseY = y;
        
       
        
    }


    void OpenGLSetup::setupMouseActiveMotion(int x, int y) {
        int id = currentInstance->pickFunction(x, y);
        currentInstance->eng->selectedBloc = id;
        currentInstance->eng->mouseX = x;
        currentInstance->eng->mouseY = y;
    }

    void OpenGLSetup::setupMousePassiveMotion(int x, int y) {
        //currentInstance->eng->selectedBlock = currentInstance->pickFunction(x, y);
        currentInstance->eng->mouseLeftClicked = false;
        currentInstance->eng->mouseRightClicked = false;
        currentInstance->eng->mouseX = x;
        currentInstance->eng->mouseY = y;
        
        
        
    }

    void OpenGLSetup::setupSpecialKeyBoard(int key, int x, int y){
        
        glutPostRedisplay();
        
    }
    
    // OpenGL window reshape routine.
     void OpenGLSetup::resize(int w, int h)
    {
        currentInstance->width = w;
        currentInstance->height = h;
        glViewport(0, 0, (GLsizei)w, (GLsizei)h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(60.0, (float)w/(float)h, 0.01, 100.0);
        glMatrixMode(GL_MODELVIEW);
        currentInstance->eng->centerX = glutGet(GLUT_WINDOW_WIDTH) / 2;
        currentInstance->eng->centerY = glutGet(GLUT_WINDOW_HEIGHT) / 2;
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
unsigned int OpenGLSetup::pickFunction(int x, int y, bool face)
{
    int viewport[4]; // Viewport data.
    
    
    glGetIntegerv(GL_VIEWPORT, viewport); // Get viewport data.
    
    unsigned int bufferPick[300000]; // Hit buffer.
    glSelectBuffer(300000, bufferPick); // Specify buffer to write hit records in selection mode
    (void) glRenderMode(GL_SELECT); // Enter selection mode.
    
    // Save the viewing volume defined in the resize routine.
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    
    // Define a viewing volume corresponding to selecting in 3 x 3 region around the cursor.
    glLoadIdentity();
    gluPickMatrix((float)x, (float)(viewport[3] - y), 0.2, 0.2, viewport);
    //glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0); // Copied from the reshape routine.
    gluPerspective(60.0, (float)width/(float)height, 0.01, 100.0);
    
    glMatrixMode(GL_MODELVIEW); // Return to modelview mode before drawing.
    glLoadIdentity();
    
    glInitNames(); // Initializes the name stack to empty.
    glPushName(0); // Puts name 0 on top of stack.
    
    // Determine hits by calling  so that names are assigned.
    eng->isSelecting = true;
    
    if(!face)
        theScene->drawScene();
    else{
        theScene->drawScene(eng->pickedBloc[eng->selectedBloc]);
        }
        
    eng->isSelecting = false;
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



// Routine to read a bitmap file.
// Works only for uncompressed bmp files of 24-bit color.
BitMapFile* OpenGLSetup::getBMPData(string filename)
{
    BitMapFile* bmp = new BitMapFile;
    unsigned int size, offset, headerSize;
    
    // Read input file name.
    ifstream infile(filename.c_str(), ios::binary);
    
    // Get the starting point of the image data.
    infile.seekg(10);
    infile.read((char *) &offset, 4);
    
    // Get the header size of the bitmap.
    infile.read((char *) &headerSize,4);
    
    // Get width and height values in the bitmap header.
    infile.seekg(18);
    infile.read( (char *) &bmp->sizeX, 4);
    infile.read( (char *) &bmp->sizeY, 4);
    
    // Allocate buffer for the image.
    size = bmp->sizeX * bmp->sizeY * 24;
    bmp->data = new unsigned char[size];
    
    // Read bitmap data.
    infile.seekg(offset);
    infile.read((char *) bmp->data , size);
    
    // Reverse color from bgr to rgb.
    int temp;
    
    for (int i = 0; i < size; i += 3)
    {
        temp = bmp->data[i];
        bmp->data[i] = bmp->data[i+2];
        bmp->data[i+2] = temp;
    }
    
    return bmp;
}

// Load external textures.
void OpenGLSetup::loadExternalTextures(string path)
{
    // Local storage for bmp image data.
    BitMapFile *image[1];
    
    // Load the texture.
    image[0] = getBMPData(path);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &bloc::texture);
    // Activate texture index texture[0].
    glBindTexture(GL_TEXTURE_2D, bloc::texture);
    
    nbTexture++;
    
    /*gluBuild2DMipmaps(GL_TEXTURE_2D, 4, 512,
                      512, GL_RGBA,GL_UNSIGNED_BYTE,
                      image[0]);*/
    
    
    
    // Set texture parameters for wrapping.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    // Set texture parameters for filtering.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    
    
    
    // Specify an image as the texture to be bound with the currently active texture index.
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[0]->sizeX, image[0]->sizeY, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image[0]->data);
     
}