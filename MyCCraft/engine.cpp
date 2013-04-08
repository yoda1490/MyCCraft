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
        while(clock() < begin_time+(1500.0)){
            sleep(1.0/60.0);
        }
    }
    
    return NULL;
}


void engine::perform(Bool* key,Bool* keyUp,Bool* keyDown){
    
    
    aMap->time+=0.0001;
    if(aMap->time>=24.0){
        aMap->time = 0;
    }
    
    if(!keyboardInitialized){
        return;
    }
    
    if(mouseRightClicked){
        cout << selectedBlock << endl;
    }
    
    if(mouseLeftClicked){
        
        vector<bloc>* lstblc = &(aMap->aRegion.listChunk.at(selectedChunk).listBloc);
        bloc* blc = &(lstblc->at(selectedBlock));
        unsigned int size = (unsigned int)lstblc->size();
        
        
        
        *blc = *new air(0, blc->position[0], blc->position[1], blc->position[2], 0.0);
        
        //set visible around bloc
        if(blc->position[1] < 256 && selectedBlock+1<size)
            lstblc->at(selectedBlock+1).visible = true;
        if(blc->position[1] > 0 && selectedBlock>0 && selectedBlock-1<size)
            lstblc->at(selectedBlock-1).visible = true;
        
        if(blc->position[2] < 15 && selectedBlock+256<size)
            lstblc->at(selectedBlock+256).visible = true;
        if(blc->position[2] > 0 && selectedBlock-256>0 && selectedBlock-256<size)
            lstblc->at(selectedBlock-256).visible = true;
        
        if(blc->position[0] < 15 && selectedBlock+4096<size)
            lstblc->at(selectedBlock+4096).visible = true;
        
        if(blc->position[0] > 0 && selectedBlock-4096>0 && selectedBlock-4096<size)
            lstblc->at(selectedBlock-4096).visible = true;        
        
    }
    
    if(player.walkMove > 1000.0){
        //player.walkMove = 0;
    }
    
    if(player.isDead()){
        //menu("dead")
        player = *(new perso);
    }
    
    if(player.positionY < 0){
        player.kill(10);
    }
    
    
    if(key[ESC]){
       exit(0);
    }
    
    if(key[DOWN_ARROW] || key[UP_ARROW])
        player.walkMove +=1*player.vitesse;
    
    
    
    if (key[DOWN_ARROW]){
        futurX = player.positionX - (vitesse * 0.015)*cos(player.angleVision)  *player.vitesse;
        futurZ = player.positionZ - (vitesse * 0.015)*sin(player.angleVision)  *player.vitesse;
    }
    if( key[UP_ARROW]){
        
        
        futurX = player.positionX + ( vitesse * 0.020)*cos(player.angleVision)  *player.vitesse;
        futurZ = player.positionZ + (vitesse * 0.020)*sin(player.angleVision)  *player.vitesse;
    }
    
    futurY = (player.positionY-(0.001*gravity));
    
    
    bool* col = collision::detectCollisions(aMap, &player, futurX, futurY, futurZ);
    
    if(!col[1]){
        player.positionY = futurY;
        player.fall += (0.001*gravity); //don't forget in jump to remove jumped size
    }else{
        if(player.fall > 3.0){
            player.fight(player.fall-3);
        }
        player.fall = 0;
    }

    
    if (key[DOWN_ARROW]){
                
        if(!col[0]){
            player.positionX = futurX;
        }
        if(!col[2]){
            player.positionZ = futurZ;
        }
    }
    if( key[UP_ARROW]){
        
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
        bool* col = collision::detectCollisions(aMap, &player, futurX, futurY, futurZ);
        if(col[1]){
          player.jump+=1.0; //to start log at 1
        }
    }
    
    if(player.jump>0){
        player.jump+= 1*vitesse;
        player.jumped += 0.008*log(player.jump) -(0.001*gravity);
        
        futurY = player.positionY + 0.008*log(player.jump);
        bool* col = collision::detectCollisions(aMap, &player, futurX, futurY, futurZ);
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
    aMap = new map("nothing yep");
}



void engine::simplePerform(Bool* key,Bool* keyUp,Bool* keyDown){
    if (key[DOWN_ARROW]){
        
        
        futurX = player.positionX - (vitesse * 0.015)*cos(player.angleVision)  *player.vitesse;
        futurZ = player.positionZ - (vitesse * 0.015)*sin(player.angleVision)  *player.vitesse;
        futurY = player.positionY;
        
        player.positionX = futurX;
        player.positionZ = futurZ;
        
    }
    if( key[UP_ARROW]){
        
        
        futurX = player.positionX + ( vitesse * 0.020)*cos(player.angleVision)  *player.vitesse;
        futurZ = player.positionZ + (vitesse * 0.020)*sin(player.angleVision)  *player.vitesse;
        futurY = player.positionY;
        
        player.positionX = futurX;
        player.positionZ = futurZ;
        
    }
    if (key[LEFT_ARROW]){
        player.angleVision -= 0.005*vitesse *player.vitesse;
    }
    if( key[RIGHT_ARROW]){
        player.angleVision += 0.005*vitesse *player.vitesse;
    }
}



