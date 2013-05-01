//
//  scene.cpp
//  MyCCraft
//
//  Created by WaWa-YoDa on 28/03/13.
//  Copyright (c) 2013 WaWa-YoDa. All rights reserved.
//

#include "scene.h"



scene::scene(engine* anEngine):
light0X(LIGHT0X), light0Y(LIGHT0Y), light0Z(LIGHT0Z), quadAtt0(QUADATT0), initialized(false)
{
    eng = anEngine;
}

void scene::setup(){
    glClearColor(0.1, 0.4, 0.5, 1.0);
    glEnable(GL_DEPTH_TEST); // Enable depth testing.
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    initialized = true;
}


void scene::drawScene(bloc* detectFace){
    
    unsigned int startTime = glutGet(GLUT_ELAPSED_TIME);
    
    if(!initialized){
        setup();
    }
    
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glLoadIdentity();
    
   
    lighting();

    
    
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
    
    
    int unsigned i=0;
    
   
    
    
    int radius = eng->visibility;
    if(eng->isSelecting){
        radius=eng->visibilitySelect;
    }
    vector<chunk*>* listC;
    if(eng->isSelecting){
        listC =  eng->aField->getNearestChunk(eng->player.positionX, eng->player.positionZ, radius);
    }else{
        listC =  eng->aField->getNearestFrontChunk(eng->player.positionX, eng->player.positionZ, eng->player.angleVision, radius);
    }
    
    if(detectFace!=NULL){
        if(detectFace->getChunk() != NULL){
            glPushMatrix();
            glTranslatef(detectFace->getChunk()->positionX, 0.0, detectFace->getChunk()->positionY);
            detectFace->draw(0.0, true);
            glPopMatrix();
        }
    }else{
        glPushMatrix();
        for(int cpt=0; cpt<listC->size(); cpt++){
            glPushMatrix();
            glTranslatef(listC->at(cpt)->positionX, 0.0, listC->at(cpt)->positionY);
            
            vector<bloc>* listB = (listC->at(cpt)->getListBloc());
            
            
            for(i=0;i< listB->size();i++){
                if(eng->isSelecting){
                    eng->pickedBloc[i+cpt] = &listB->at(i);
                    glLoadName(i+cpt);
                }
                try{
                    if(listB->at(i).getChunk() == NULL)  listB->at(i).setChunk(listC->at(cpt));
                    listB->at(i).draw(eng->aField->time);
                }catch(exception e){
                    cout << "Error ..." << endl;
                }
            }
            glPopMatrix();
        }
        glPopMatrix();
    }
    
    glutSwapBuffers();
    
    
    
    
    
    
}




void scene::lighting(void) {
	// Turn on OpenGL lighting.
    glEnable(GL_LIGHTING);
    
    
    
    // Light property vectors.
    //float lightAmb[] = { 0.0, 0.0, 0.0, 1.0 };
    float lightDifAndSpec0[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat globAmb[] = {
        static_cast<GLfloat>(0.4*sin(2*3.14*(1.0/24.0)*eng->aField->time-3.14/2)+0.6),
        static_cast<GLfloat>(0.4*sin(2*3.14*(1.0/24.0)*eng->aField->time-3.14/2)+0.6),
        static_cast<GLfloat>(0.4*sin(2*3.14*(1.0/24.0)*eng->aField->time-3.14/2)+0.6), 0.5f };
    
    GLfloat light0_position[3] ;
    
    light0_position[0] = light0X;
    light0_position[1] = light0Y;
    light0_position[2] = light0Z;
    
    
    // Light0 properties.
    glLightfv(GL_LIGHT0, GL_AMBIENT, globAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpec0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightDifAndSpec0);
    glLightfv(GL_LIGHT0,GL_POSITION,light0_position);
    
    
    glEnable(GL_LIGHT0); // Enable particular light source.
    //glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lightAmb); // Global ambient light.
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
    
    GLfloat diffuse[] = {0.8f,0.8f,0.8f,0.8f};
    //GLfloat specular[] = {0.8f,0.8f,0.8f,0.8f};
    GLfloat specular_reflexion[] = {0.0f,0.0f,0.0f,0.0f};
    GLubyte shiny_obj = 128;
    
    //spécification de la réflexion sur les matériaux
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,diffuse);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,specular_reflexion);
    glMateriali(GL_FRONT_AND_BACK,GL_SHININESS,shiny_obj);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1); // Enable local viewpoint
    
    
    
}