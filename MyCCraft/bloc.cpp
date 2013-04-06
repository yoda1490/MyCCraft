//
//  block.cpp
//  MyCCraft
//
//  Created by WaWa-YoDa on 28/03/13.
//  Copyright (c) 2013 WaWa-YoDa. All rights reserved.
//

#include "bloc.h"


//copy constructor
bloc::bloc(const bloc &source){
    diff = source.diff; // red and blue diffuse reflectance of the submarine monster
    emi = source.emi; // red and blue emittance of the submarine monster
    
    spec = source.spec; // White specular reflectance.
    shi = source.shi; // Shininess.
    
    position[0] = source.position[0];
    position[1] = source.position[1];
    position[2] = source.position[2];
    orient = source.orient;
    size = source.size;
    color[0] = source.color[0];
    color[1] = source.color[1];
    color[2] = source.color[2];
    color[3] = source.color[3];
    textureURL = source.textureURL;
    
    visible = source.visible;

}

bloc::bloc(int idBloc, float x, float y, float z, float orientation){
    
}

bloc::bloc(float x, float y, float z, float orientation, float colorX, float colorY, float colorZ, float colorA, float aSize){
    size = aSize;
    position[0] = x;
    position[1] = y;
    position[2] = z;
    orient = orientation;
    color[0] = colorX;
    color[1] = colorY;
    color[2] = colorZ;
    color[3] = colorA;
}


bloc::bloc(float x, float y, float z, float orientation, float colorX, float colorY, float colorZ, float colorA){
    position[0] = x;
    position[1] = y;
    position[2] = z;
    orient = orientation;
    color[0] = colorX;
    color[1] = colorY;
    color[2] = colorZ;
    color[3] = colorA;
}

void bloc::draw(bool selected){
    if(!visible)
        return;
    glPushMatrix();
    light();
    glTranslatef(position[0],position[1],position[2]);
    glRotatef(orient, 0.0, 1.0, 0.0);
    if(selected){
        glutSolidCube(size-0.01);
    }else
        glutSolidCube(size);
    
    float matAmb[] = {color[0]-color[1], color[2]+color[1], color[1], color[3]};
    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmb);
    glRotatef(45.0, 0.0, 1.0, 0.0);
    glRotatef(45.0, 1.0, 0.0, 0.0);
    glutSolidCube(size-0.35);
    glPopMatrix();
}

void bloc::light(){
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