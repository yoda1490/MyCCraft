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
        walkMove +=1*player.vitesse;
        
        futurX = player.positionX - (vitesse * 0.015)*cos(player.angleVision)  *player.vitesse;
        futurZ = player.positionZ - (vitesse * 0.025)*sin(player.angleVision)  *player.vitesse;
        futurY = player.positionY;
        
        bool* col = collision::detectCollisions(&listBloc, &player, futurX, futurY, futurZ);
        
        if(!col[0]){
            player.positionX = futurX;
        }
        if(!col[2]){
            player.positionZ = futurZ;
        }
    }
    if( key[UP_ARROW]){
        walkMove +=1*player.vitesse;
        
        futurX = player.positionX + ( vitesse * 0.015)*cos(player.angleVision)  *player.vitesse;
        futurZ = player.positionZ + (vitesse * 0.015)*sin(player.angleVision)  *player.vitesse;
        futurY = player.positionY;
        
        bool* col = collision::detectCollisions(&listBloc, &player, futurX, futurY, futurZ);
        
        if(!col[0]){
            player.positionX = futurX;
        }
        if(!col[2]){
            player.positionZ = futurZ;
        }
    }
    if (key[LEFT_ARROW]){
        player.angleVision -= 0.0025*vitesse *player.vitesse;
    }
    if( key[RIGHT_ARROW]){
        player.angleVision += 0.0025*vitesse *player.vitesse;
    }
    if (key[GLUT_KEY_PAGE_DOWN]){
        player.positionY -= 0.0025*vitesse *player.vitesse;
    }
    if( key[GLUT_KEY_PAGE_UP]){
        player.positionY += 0.0025*vitesse *player.vitesse;
    }
    
    
    if( !key['v'] && viewModePressed){
        viewModePressed = false;
    }
    if( keyDown['v'] && !viewModePressed){
        viewMode = (viewMode+1)%3;
        viewModePressed = true;
    }
    
    

}



void engine::loadMap(string fileName){
    for(int x=0; x< 100; x++){
        for(int z=0; z< 100; z++){
            listBloc.push_back(new bloc(x, 0, z, 0.0, 0.2, 0.6, 0.2, 1.0));
        }
    }
    
    listBloc.push_back(new bloc(25.0, 1.0, 25.0, 90.0, 0.6, 0.2, 0.2, 1.0));
    
   
    
    listBloc.push_back(new bloc(5.0, 1.0, 0.0, 0.0, 0.6, 0.2, 0.2, 1.0, 1.0));
    listBloc.push_back(new bloc(5.0, 2.0, 0.0, 0.0, 0.6, 0.2, 0.2, 1.0, 1.0));
    listBloc.push_back(new bloc(5.0, 3.0, 0.0, 0.0, 0.6, 0.2, 0.2, 1.0, 1.0));
    listBloc.push_back(new bloc(5.0, 3.0, 1.0, 0.0, 0.6, 0.2, 0.2, 1.0, 1.0));
    listBloc.push_back(new bloc(5.0, 3.0, 2.0, 0.0, 0.6, 0.2, 0.2, 1.0, 1.0));
    listBloc.push_back(new bloc(5.0, 2.0, 2.0, 0.0, 0.6, 0.2, 0.2, 1.0, 1.0));
    listBloc.push_back(new bloc(5.0, 1.0, 2.0, 0.0, 0.6, 0.2, 0.2, 1.0, 1.0));
}






