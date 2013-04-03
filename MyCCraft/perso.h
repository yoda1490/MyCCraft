//
//  Perso.h
//  MyCCraft
//
//  Created by WaWa-YoDa on 03/04/13.
//  Copyright (c) 2013 WaWa-YoDa. All rights reserved.
//

#ifndef __MyCCraft__Perso__
#define __MyCCraft__Perso__

#include <iostream>
#include <string>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;

class perso{
    
public:
    float angleVision = -3.14/2.5;
    float positionX = 0, positionY = 0.5, positionZ = 0; //positionY == foot
    float hauteurEye = 1.6;
    string name = "Player";
    float vitesse = 1;
    
    
    float diff = 0.1; // red and blue diffuse reflectance of the submarine monster
    float emi = 0.1; // red and blue emittance of the submarine monster
    
    float spec = 1.0; // White specular reflectance.
    float shi = 30.0; // Shininess.
    float color[4];
    
    float tailleX = 0.8;
    float tailleY = 1.8;
    float tailleZ = 0.5;
    
    float hitbox = 0.4; //for collision detection, if in a circle of hitbox
    
    void draw();
    void light();
    
    
};

#endif /* defined(__MyCCraft__Perso__) */
