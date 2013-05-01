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
#include <cmath>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;

static float ANGVIS = 3.14f/4.0f, POSITIONX = 0.0f, POSITIONY = 10.5f, POSITIONZ = 0.0f, HEIGHTEYE = 1.6f;
static string NAME = "Player";
static float SPEED = 1, LIFE=10.0, ARMUR=10.0;
static float DIFFU = 0.1f, EMIS = 0.1f, SPECU = 1.0, SHIN = 30.0;
static float SIZEX = 0.8f, SIZEY = 1.8f, SIZEZ = 0.5f, HITBOX = 0.4f;
static float WALKMOVE = 0, FREQUENCYMOVE = 0.0025f; //speed of walkmove: we add sin(2PI*frequencyMove*walkMove) to y view
static float JUMP = 0.0f, JUMPED = 0.0f, JUMPMAX = 1.8f, FALL = 0.0f; //height fallen



class perso{
    
public:
    float angleVision;
    float positionX, positionY, positionZ; //positionY == foot
    float hauteurEye;
    string name;
    float vitesse;
    
    
    float life;
    float armur;
    
    
    float diff; // red and blue diffuse reflectance of the submarine monster
    float emi; // red and blue emittance of the submarine monster
    
    float spec; // White specular reflectance.
    float shi; // Shininess.
    float color[4];
    
    float tailleX;
    float tailleY;
    float tailleZ;
    
    float hitbox; //for collision detection, if in a circle of hitbox
    
    float walkMove; //when you move your vision move up/down
    float frequencyMove; //speed of walkmove: we add sin(2PI*frequencyMove*walkMove) to y view
    
    float jump; //time counter for jumping
    float jumped; //height jumped
    float jumpMax; //max high (in y) that can be jumped
    
    float fall; //height fallen
    
	perso();
    void kill(float hurt); //remove life
    void fight(float hurt); //remove armur
    bool isDead();
    
    void draw();
    void light();
    
    
    
    
};

#endif /* defined(__MyCCraft__Perso__) */
