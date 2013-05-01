//
//  block.cpp
//  MyCCraft
//
//  Created by WaWa-YoDa on 28/03/13.
//  Copyright (c) 2013 WaWa-YoDa. All rights reserved.
//

#include "bloc.h"

GLuint bloc::texture;


//copy constructor
bloc::bloc(const bloc &source){
    diff = source.diff; // red and blue diffuse reflectance of the submarine monster
    emi = source.emi; // red and blue emittance of the submarine monster
    
    spec = source.spec; // White specular reflectance.
    shi = source.shi; // Shininess.
    
    positionX = source.positionX;
    positionY = source.positionY;
    positionZ = source.positionZ;
    orient = 0.0;
    size = source.size;
    color[0] = source.color[0];
    color[1] = source.color[1];
    color[2] = source.color[2];
    color[3] = source.color[3];
    textureURL = source.textureURL;
    
    visible = source.visible;
    
    initialized = source.initialized;
    
    idBloc = source.idBloc;
    
    owner = source.owner;

}

bloc::bloc(int idB, float x, float y, float z, float orientation):
diff(DIFF), emi(EMI), spec(SPEC), shi(SHI), owner(NULL), visible(VISIBLE)
{
    initialized = true;
    idBloc = idB;
    size = 1.0;
    positionX = x;
    positionY = y;
    positionZ = z;
    orient = 0.0;
    color[0] = 1.0;
    color[1] = 1.0;
    color[2] = 1.0;
    color[3] = 1.0;

    
}

bloc::bloc(float x, float y, float z, float orientation, float colorX, float colorY, float colorZ, float colorA, float aSize):
diff(DIFF), emi(EMI), spec(SPEC), shi(SHI), owner(NULL), visible(VISIBLE), idBloc(IDBLOC){
    initialized = true;
    size = aSize;
    positionX = x;
    positionY = y;
    positionZ = z;
    orient = 0.0;
    color[0] = colorX;
    color[1] = colorY;
    color[2] = colorZ;
    color[3] = colorA;
}


bloc::bloc(float x, float y, float z, float orientation, float colorX, float colorY, float colorZ, float colorA):
idBloc(IDBLOC), diff(DIFF), emi(EMI), spec(SPEC), shi(SHI), owner(NULL), visible(VISIBLE), size(SIZEDEF){
    initialized = true;
    positionX = x;
    positionY = y;
    positionZ = z;
    orient = 0.0;
    color[0] = colorX;
    color[1] = colorY;
    color[2] = colorZ;
    color[3] = colorA;
}

void bloc::draw(float time, bool picking){
    if(!visible || idBloc == 0)
        return;
    glPushMatrix();
    light(time);
    glTranslatef(positionX,positionY,positionZ);
    //glRotatef(orient, 0.0, 1.0, 0.0); --> awfull to detect face if bloc can have orientation
    
    float sizeDrawed = size-0.0001;
    
    
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
    
    if(idBloc>0){
        // Enable texturing and filled polygon mode.
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);
    }
    

    for (i = 5; i >= 0; i--) {
        if(picking){
            glLoadName(i+1);
        }
        glBegin(GL_QUADS);
        glNormal3fv(&n[i][0]);
        glTexCoord2f(0.0, 0.25); glVertex3fv(&v[faces[i][0]][0]);
        glTexCoord2f(0.0, 0.0); glVertex3fv(&v[faces[i][1]][0]);
        glTexCoord2f(0.25, 0.0); glVertex3fv(&v[faces[i][2]][0]);
        glTexCoord2f(0.25, 0.25); glVertex3fv(&v[faces[i][3]][0]);
        glEnd();
    }
    
    if(idBloc>0) glDisable(GL_TEXTURE_2D);
    
    
    glPopMatrix();
}

void bloc::light(float time){
    // Material property vectors.
    /*GLfloat matAmb[] = {
        static_cast<GLfloat>((color[0]+0.4*sin(2*3.14*(1.0/24.0)*time-3.14/2)+0.6)),
        static_cast<GLfloat>((color[1]+0.4*sin(2*3.14*(1.0/24.0)*time-3.14/2)+0.6)),
        static_cast<GLfloat>((color[2]+0.4*sin(2*3.14*(1.0/24.0)*time-3.14/2)+0.6)), color[3]};
    
    float matAmb[] = {color[0], color[1], color[2], color[3]};
    //float matAmb[] = {1.2, 1.6, 1.2, 0.0};
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
     
     */
    //float matAmb[] = {color[0], color[1], color[2], color[3]};
    //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmb);
    //glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matAmb);
    //glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matAmb);
    
    
   glColor3f(color[0], color[1], color[2]);
}



void bloc::setChunk(chunk* c){
    owner = c;
    
}


chunk* bloc::getChunk(){
    return owner;
}




