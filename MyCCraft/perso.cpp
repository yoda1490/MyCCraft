//
//  Perso.cpp
//  MyCCraft
//
//  Created by WaWa-YoDa on 03/04/13.
//  Copyright (c) 2013 WaWa-YoDa. All rights reserved.
//

#include "Perso.h"


void perso::draw(){
    
    glPushMatrix();
    light();
    glTranslatef(positionX+tailleX/2,positionY+tailleY/2,positionZ+tailleZ/2);
    glRotatef(360.0-((angleVision/3.14)*180.0), 0.0, 1.0, 0.0);
    //glutSolidCube(0.5);
    glutSolidTeapot(0.5);
    glTranslatef(0.0,0.5,0.0);
    glutSolidCube(0.4);
    glPopMatrix();
    //cout << positionX << ":" << positionZ << endl;

    
}

void perso::light(){
    // Material property vectors.
    float matAmb[] = {color[0], color[1], color[2], color[3]};
    float matDif[] = {diff, diff, diff, 1.0};
    float matSpec[] = { spec, spec, spec, 1.0 };
    float matShine[] = { shi };
    float matEmission[] = {emi, emi, emi, 1.0};
    
    
    // Material properties of the block
    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
    glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
}