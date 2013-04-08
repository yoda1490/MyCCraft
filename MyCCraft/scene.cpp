//
//  scene.cpp
//  MyCCraft
//
//  Created by WaWa-YoDa on 28/03/13.
//  Copyright (c) 2013 WaWa-YoDa. All rights reserved.
//

#include "scene.h"



scene::scene(engine* anEngine){
    eng = anEngine;
}

void scene::setup(){
    glClearColor(0.1, 0.4, 0.5, 1.0);
    glEnable(GL_DEPTH_TEST); // Enable depth testing.
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    initialized = true;
}


void scene::drawScene(){
    
    unsigned int startTime = glutGet(GLUT_ELAPSED_TIME);
    
    if(!initialized){
        setup();
    }
    
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glLoadIdentity();
    
   
    
    
    
    eng->visionX = eng->player.positionX + 10 * cos(eng->player.angleVision)+ (eng->player.tailleX+0.01) * cos(eng->player.angleVision);
    eng->visionY = eng->player.positionY ;
    eng->visionZ = eng->player.positionZ + 10 * sin(eng->player.angleVision)+ (eng->player.tailleX+0.01) * cos(eng->player.angleVision);
    if(eng->viewMode == 0){
    gluLookAt(
              eng->player.positionX,
              eng->player.positionY+eng->player.hauteurEye+(eng->player.tailleY/20.0)*sin(6.28*eng->player.frequencyMove*eng->player.walkMove) ,
              eng->player.positionZ,
              
              eng->visionX,
              eng->visionY+(eng->player.tailleY/20.0)*sin(6.28*eng->player.frequencyMove*eng->player.walkMove),
              eng->visionZ,
              
              0.0,
              1.0,
              0.0);
    }else if(eng->viewMode == 1){
    gluLookAt(
              eng->godX,
              eng->godY,
              eng->godZ,
              
              eng->player.positionX,
              eng->player.positionY+eng->player.hauteurEye,
              eng->player.positionZ,
              
              0.0,
              1.0,
              0.0);
        eng->player.draw();
    }else{
        gluLookAt(
                  eng->player.positionX - 5 * cos(eng->player.angleVision),
                  eng->player.positionY+2,
                  eng->player.positionZ - 5 * sin(eng->player.angleVision),
                  
                  eng->visionX,
                  eng->visionY,
                  eng->visionZ,
                  
                  0.0,
                  1.0,
                  0.0);
        eng->player.draw();
    }
    
    lighting();
    
    int unsigned i=0;
    
   
    //chunk* listChunk = eng->aMap->getNearestChunk(eng->player.positionX, eng->player.positionY);
    
    
    /*for(int cpt=0; cpt<9; cpt++){
    
        for(i=0;i< listChunk[cpt].listBloc.size();i++){
                if(eng->isSelecting){
                    glLoadName(i +(cpt*100000) + (0*1000000));
                }
                //listChunk[cpt]->listBloc[i]->draw(eng->selectedBlock==i);
            eng->aMap->regions[0]->listChunk.at(0).listBloc.at(cpt);
        }
    }*/
    
    int nbChunk = 0;
    vector<chunk>* listC =  eng->aMap->aRegion.getNearestChunk(eng->player.positionX, eng->player.positionY, &nbChunk);
    
    
    glPushMatrix();
        glTranslatef(eng->aMap->aRegion.positionX, 0.0, eng->aMap->aRegion.positionY);
        for(int cpt=0; cpt<nbChunk; cpt++){
            glPushMatrix();
            glTranslatef(eng->aMap->aRegion.listChunk.at(cpt).positionX, 0.0, eng->aMap->aRegion.listChunk.at(cpt).positionY);
            vector<bloc>* listB = &(listC->at(cpt).listBloc);
    
            for(i=0;i< listB->size();i++){
                if(eng->isSelecting){
                    glLoadName(i+(16*16*256*cpt));
                }
                listB->at(i).draw();
            }
            glPopMatrix();
        }
    glPopMatrix();
    
    glutSwapBuffers();
    
    
    while(glutGet(GLUT_ELAPSED_TIME) < startTime+(  (1/eng->fps)*1000 )){
        sleep(1.0/60.0);
    }
    
    
    
}




void scene::lighting(void) {
	// Turn on OpenGL lighting.
    glEnable(GL_LIGHTING);
    
    
        
    // Light property vectors.
    float lightAmb[] = { 0.0, 0.0, 0.0, 1.0 };
    float lightDifAndSpec0[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat globAmb[] = {
        static_cast<GLfloat>(0.4*sin(2*3.14*(1.0/24.0)*eng->aMap->time-3.14/2)+0.6),
        static_cast<GLfloat>(0.4*sin(2*3.14*(1.0/24.0)*eng->aMap->time-3.14/2)+0.6),
        static_cast<GLfloat>(0.4*sin(2*3.14*(1.0/24.0)*eng->aMap->time-3.14/2)+0.6), 0.5f };
    
    GLfloat light0_position[3] ;
    
    light0_position[0] = light0X;
    light0_position[1] = light0Y;
    light0_position[2] = light0Z;
    
    
    // Light0 properties.
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpec0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightDifAndSpec0);
    glLightfv(GL_LIGHT0,GL_POSITION,light0_position);
    
    
    glEnable(GL_LIGHT0); // Enable particular light source.
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb); // Global ambient light.
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE); // Enable local viewpoint
    
    
    // Light quadratic attenuation factor.
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, quadAtt0);
    
    //draw a ball to simulate the  light
    glDisable(GL_LIGHTING);
    glPushMatrix();
    //glLightfv(GL_LIGHT0,GL_POSITION,light0_position);
    glColor3f(0.5, 0.5, 0.0);
    glTranslatef(light0X, light0Y, light0Z);
    glutSolidSphere(1,20,20);
    glPopMatrix();
    glEnable(GL_LIGHTING);
    
    
}