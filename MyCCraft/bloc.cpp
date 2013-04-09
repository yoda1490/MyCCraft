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
    
    positionX = source.positionX;
    positionY = source.positionY;
    positionZ = source.positionZ;
    orient = source.orient;
    size = source.size;
    color[0] = source.color[0];
    color[1] = source.color[1];
    color[2] = source.color[2];
    color[3] = source.color[3];
    textureURL = source.textureURL;
    
    visible = source.visible;
    
    initialized = source.initialized;

}

bloc::bloc(int idBloc, float x, float y, float z, float orientation){
    initialized = true;
}

bloc::bloc(float x, float y, float z, float orientation, float colorX, float colorY, float colorZ, float colorA, float aSize){
    initialized = true;
    size = aSize;
    positionX = x;
    positionY = y;
    positionZ = z;
    orient = orientation;
    color[0] = colorX;
    color[1] = colorY;
    color[2] = colorZ;
    color[3] = colorA;
}


bloc::bloc(float x, float y, float z, float orientation, float colorX, float colorY, float colorZ, float colorA){
    initialized = true;
    positionX = x;
    positionY = y;
    positionZ = z;
    orient = orientation;
    color[0] = colorX;
    color[1] = colorY;
    color[2] = colorZ;
    color[3] = colorA;
}

void bloc::draw(){
    if(!visible)
        return;
    glPushMatrix();
    light();
    glTranslatef(positionX,positionY,positionZ);
    glRotatef(orient, 0.0, 1.0, 0.0);
    
    float sizeDrawed = size;
    
    
    static GLfloat n[6][3] =
    {
        {-1.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        {1.0, 0.0, 0.0},
        {0.0, -1.0, 0.0},
        {0.0, 0.0, 1.0},
        {0.0, 0.0, -1.0}
    };
    static GLint faces[6][4] =
    {
        {0, 1, 2, 3},
        {3, 2, 6, 7},
        {7, 6, 5, 4},
        {4, 5, 1, 0},
        {5, 6, 2, 1},
        {7, 4, 0, 3}
    };
    GLfloat v[8][3];
    GLint i;
    
    v[0][0] = v[1][0] = v[2][0] = v[3][0] = -sizeDrawed / 2;
    v[4][0] = v[5][0] = v[6][0] = v[7][0] = sizeDrawed / 2;
    v[0][1] = v[1][1] = v[4][1] = v[5][1] = -sizeDrawed / 2;
    v[2][1] = v[3][1] = v[6][1] = v[7][1] = sizeDrawed / 2;
    v[0][2] = v[3][2] = v[4][2] = v[7][2] = -sizeDrawed / 2;
    v[1][2] = v[2][2] = v[5][2] = v[6][2] = sizeDrawed / 2;
    
    for (i = 5; i >= 0; i--) {
        glBegin(GL_QUADS);
        glNormal3fv(&n[i][0]);
        glVertex3fv(&v[faces[i][0]][0]);
        glVertex3fv(&v[faces[i][1]][0]);
        glVertex3fv(&v[faces[i][2]][0]);
        glVertex3fv(&v[faces[i][3]][0]);
        glEnd();
    }
    
    glPopMatrix();
}

void bloc::light(){
    // Material property vectors.
    float matAmb[] = {color[0], color[1], color[2], color[3]};
    /*float matDif[] = {diff, diff, diff, 1.0};
    float matSpec[] = { spec, spec, spec, 1.0 };
    float matShine[] = { shi };
    float matEmission[] = {emi, emi, emi, 1.0};**/
    
    
    // Material properties of the block
    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmb);
    /*glMaterialfv(GL_FRONT, GL_DIFFUSE, matDif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
    glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);**/
}