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
    
    initialized = true;
}


void scene::drawScene(){
    if(!initialized){
        setup();
    }
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    
    
    eng->visionX = eng->positionX + 10 * cos(eng->angleVision);
    eng->visionY = eng->positionY - 5;
    eng->visionZ = eng->positionZ + 10 * sin(eng->angleVision);
    gluLookAt(eng->positionX,eng->positionY,eng->positionZ,  eng->visionX,eng->visionY,eng->visionZ,  0.0,1.0,0.0);
    
    lighting();
    

    for(int unsigned i=0;i<eng->listBloc.size();i++){
        eng->listBloc[i]->draw();
    }
    
    
    
    bloc bloc(25, 1, 25, 45.0, 0.6, 0.2, 0.2, 1.0);
    bloc.draw();
    
    glutSwapBuffers();
     
    
}




void scene::lighting(void) {
	// Turn on OpenGL lighting.
    glEnable(GL_LIGHTING);
    
    
        
    // Light property vectors.
    float lightAmb[] = { 0.0, 0.0, 0.0, 1.0 };
    float lightDifAndSpec0[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat globAmb[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    
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