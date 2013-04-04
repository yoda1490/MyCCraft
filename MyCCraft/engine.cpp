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

void engine::setScene(class scene *aScene){
    scene = aScene;
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
    
    return NULL;
}


void engine::perform(Bool* key,Bool* keyUp,Bool* keyDown){
    
    if(!keyboardInitialized){
        return;
    }
    
    if(mouseLeftClicked){
        //if(contextInitialized)
            //pickFunction(mouseX, mouseY);
    }
    
    if(player.walkMove > 1000.0){
        //player.walkMove = 0;
    }
    
    if(player.isDead()){
        //menu("dead")
        player = *(new perso);
    }
    
    if(player.positionY < -128.0){
        player.kill(10);
    }
    
    futurY = (player.positionY-(0.001*gravity));
    bool* col = collision::detectCollisions(&listBloc, &player, player.positionX, futurY, player.positionZ);
    if(!col[1]){
        player.positionY = futurY;
        player.fall += (0.001*gravity); //don't forget in jump to remove jumped size
    }else{
        if(player.fall > 3.0){
            player.fight(player.fall-3);
        }
        player.fall = 0;
    }
    
    if(key[ESC]){
       exit(0);
    }
    if (key[DOWN_ARROW]){
        player.walkMove +=1*player.vitesse;
        
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
        player.walkMove +=1*player.vitesse;
        
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
        player.angleVision -= 0.005*vitesse *player.vitesse;
    }
    if( key[RIGHT_ARROW]){
        player.angleVision += 0.005*vitesse *player.vitesse;
    }
    if (key[GLUT_KEY_PAGE_DOWN]){
        player.positionY -= 0.005*vitesse *player.vitesse;
    }
    if( key[GLUT_KEY_PAGE_UP]){
        player.positionY += 0.005*vitesse *player.vitesse;
    }
    
    
    if( !key['v'] && viewModePressed){
        viewModePressed = false;
    }
    if( key['v'] && !viewModePressed){
        viewMode = (viewMode+1)%3;
        viewModePressed = true;
    }
    
    if( key[' '] && player.jump==0){
        futurY = player.positionY-0.1;
        bool* col = collision::detectCollisions(&listBloc, &player, player.positionX, futurY, player.positionZ);
        if(col[1]){
          player.jump+=1.0; //to start log at 1
        }
    }
    
    if(player.jump>0){
        player.jump+= 1*vitesse;
        player.jumped += 0.008*log(player.jump) -(0.001*gravity);
        
        futurY = player.positionY + 0.008*log(player.jump);
        bool* col = collision::detectCollisions(&listBloc, &player, player.positionX, futurY, player.positionZ);
        if(!col[1]){
            player.positionY = futurY;
            player.fall -=  0.008*log(player.jump);
        }
        
        if(player.jumped>=player.jumpMax){
            player.jumped = 0;
            player.jump = -1.0;
        }
    }
    
    if( !key[' '] && player.jump == -1.0){
        player.jump = 0;
    }
    
    if( !key['z'])
       godX-=0.1;
    if( !key['s'])
        godX+=0.1;
    
    if( !key['a'])
        godY+=0.1;
    if( !key['e'])
        godY-=0.1;
    
    
    if( !key['q'])
        godZ+=0.1;
    if( !key['d'])
        godZ-=0.1;
    
    

}



void engine::loadMap(string fileName){
    for(int x=0; x< 48; x++){
        for(int z=0; z< 48; z++){
            listBloc.push_back(new bloc(x, 0, z, 0.0, 0.2, 0.6, 0.2, 1.0));
        }
    }
    
    for(int cpt=0; cpt<10; cpt++){
        listBloc.push_back(new bloc(24.0, 1.0+cpt, 25.0-cpt, 90.0, 0.6, 0.2, (float)cpt/10.0, 1.0));
        listBloc.push_back(new bloc(25.0, 1.0+cpt, 25.0-cpt, 90.0, 0.6, 0.2, (float)cpt/10.0, 1.0));
        listBloc.push_back(new bloc(26.0, 1.0+cpt, 25.0-cpt, 90.0, 0.6, 0.2, (float)cpt/10.0, 1.0));
    }
    
   
    for(int cpt=0; cpt < 10; cpt++){
    listBloc.push_back(new bloc(cpt+5.0, 1.0, 0.0, 0.0, 0.6, (float)cpt/10.0, 0.2, 1.0, 1.0));
    listBloc.push_back(new bloc(cpt+5.0, 2.0, 0.0, 0.0, 0.6, (float)cpt/10.0, 0.2, 1.0, 1.0));
    listBloc.push_back(new bloc(cpt+5.0, 3.0, 0.0, 0.0, 0.6, (float)cpt/10.0, 0.2, 1.0, 1.0));
    listBloc.push_back(new bloc(cpt+5.0, 3.0, 1.0, 0.0, 0.6, (float)cpt/10.0, 0.2, 1.0, 1.0));
    listBloc.push_back(new bloc(cpt+5.0, 3.0, 2.0, 0.0, 0.6, (float)cpt/10.0, 0.2, 1.0, 1.0));
    listBloc.push_back(new bloc(cpt+5.0, 2.0, 2.0, 0.0, 0.6, (float)cpt/10.0, 0.2, 1.0, 1.0));
    listBloc.push_back(new bloc(cpt+5.0, 1.0, 2.0, 0.0, 0.6, (float)cpt/10.0, 0.2, 1.0, 1.0));
    }
    
    
}





