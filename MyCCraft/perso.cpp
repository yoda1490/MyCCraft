//
//  Perso.cpp
//  MyCCraft
//
//  Created by WaWa-YoDa on 03/04/13.
//  Copyright (c) 2013 WaWa-YoDa. All rights reserved.
//

#include "Perso.h"

void perso::kill(float hurt){
    life -=hurt;
}
void perso::fight(float hurt){
    armur -= hurt;
    if(armur > 1.0)
        life -= hurt-(armur-1.0);
    else
        life -= hurt-armur;
    
    cout << "fight:" << hurt << endl;
}
bool perso::isDead(){
    if(life <=0)
        return true;
    return false;
}


void perso::draw(){
    
    glPushMatrix();
    light();
    glTranslatef(positionX,positionY,positionZ);
    glRotatef(360.0-((angleVision/3.14)*180.0), 0.0, 1.0, 0.0);
    
    
    glTranslatef(0,0.125,0.0);
    //foot
    
    glPushMatrix();
        glTranslatef(0.0, 0.75, 0);
        glRotatef(20*cos(2*3.14*(frequencyMove/2)*walkMove), 0.0, 0.0, 1.0);
        glTranslatef(0.0, -0.75, 0);
    
        glPushMatrix();
            glTranslatef(0,0.0,-0.13);
            glutSolidCube(0.25);
            glTranslatef(0,0.25,0.0);
            glutSolidCube(0.25);
            glTranslatef(0,0.25,0.0);
            glutSolidCube(0.25);
        glPopMatrix();
    
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.0, 0.75, 0);
        glRotatef(-20*cos(2*3.14*(frequencyMove/2)*walkMove), 0.0, 0.0, 1.0);
        glTranslatef(0.0, -0.75, 0);
    
        glPushMatrix();
            glTranslatef(0,0.0,0.13);
            glutSolidCube(0.25);
            glTranslatef(0,0.25,0.0);
            glutSolidCube(0.25);
            glTranslatef(0,0.25,0.0);
            glutSolidCube(0.25);
        glPopMatrix();
    glPopMatrix();

    
    
    glTranslatef(0,0.25,0.0);
    //body
    glPushMatrix();
        glTranslatef(0,0.0,-0.125);
        glutSolidCube(0.25);
    
        glTranslatef(0,0.25,0);
        glutSolidCube(0.25);
    
        glTranslatef(0,0.25,0);
        glutSolidCube(0.25);
    
        glTranslatef(0,0.25,0);
        glutSolidCube(0.25);
    
        glTranslatef(0,0.25,0);
        glutSolidCube(0.25);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(0,0.0,0.125);
        glutSolidCube(0.25);
    
        glTranslatef(0,0.25,0);
        glutSolidCube(0.25);
    
        glTranslatef(0,0.25,0);
        glutSolidCube(0.25);
    
        glTranslatef(0,0.25,0);
        glutSolidCube(0.25);
    
        glTranslatef(0,0.25,0);
        glutSolidCube(0.25);
    glPopMatrix();
    
    glTranslatef(0,0.50,0.0);
    
    //hands
    glPushMatrix();
        glTranslatef(0,0.0,-0.290);
        glutSolidCube(0.25);
    
        glTranslatef(0,0.25,0);
        glutSolidCube(0.25);
    
        glTranslatef(0,0.25,0);
        glutSolidCube(0.25);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(0,0.0,0.290);
        glutSolidCube(0.25);
    
        glTranslatef(0,0.25,0);
        glutSolidCube(0.25);
    
        glTranslatef(0,0.25,0);
        glutSolidCube(0.25);
    glPopMatrix();
    
    //head
    glPushMatrix();
        glTranslatef(0,0.85,0.0);
        glutSolidCube(0.40);
    glPopMatrix();


    
    
    


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