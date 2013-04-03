//
//  engin.cpp
//  MyCCraft
//
//  Created by WaWa-YoDa on 28/03/13.
//  Copyright (c) 2013 WaWa-YoDa. All rights reserved.
//

#include "engine.h"

static engine* currentInstance;

void engine::setSession(class OpenGLSetup *aSession){
    session = aSession;
}


void engine::start()
{
    // On crée un thread
    pthread_t thread;
    
    currentInstance = this;
    
    // Permet d'exécuter le fonction maFonction en parallèle
    pthread_create(&thread, NULL, engine::run, NULL);

}

void* engine::run(void*){
    clock_t begin_time = clock();
    while (currentInstance->state > 0) {
        begin_time = clock();
        currentInstance->perform(currentInstance->session->getKeys(), currentInstance->session->getKeysUp(), currentInstance->session->getKeysDown());
        while(clock() < begin_time+(1000.0)){
            sleep(1.0/60.0);
        }
    }
}


void engine::perform(Bool* key,Bool* keyUp,Bool* keyDown){
    
    
    if(key[ESC]){
       exit(0);}
    if (key[DOWN_ARROW]){
        positionX -= (vitesse * 0.05)*cos(angleVision) ;  positionZ -= (vitesse * 0.05)*sin(angleVision) ;}
    if( key[UP_ARROW]){
        positionX += ( vitesse * 0.05)*cos(angleVision) ;  positionZ += (vitesse * 0.05)*sin(angleVision) ;}
    if (key[LEFT_ARROW]){
        angleVision -= 0.005*(vitesse/2.0);}
    if( key[RIGHT_ARROW]){
        angleVision += 0.005*(vitesse/2.0);}
    if (key[GLUT_KEY_PAGE_DOWN]){
        positionY -= 0.005*(vitesse/2.0);}
    if( key[GLUT_KEY_PAGE_UP]){
        positionY += 0.005*(vitesse/2.0);}

}



void engine::loadMap(string fileName){
    for(int x=0; x< 100; x++){
        for(int z=0; z< 100; z++){
            listBloc.push_back(new bloc(x, 0, z, 0.0, 0.2, 0.6, 0.2, 1.0));
        }
    }
}






