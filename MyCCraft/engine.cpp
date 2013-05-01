//
//  engin.cpp
//  MyCCraft
//
//  Created by WaWa-YoDa on 28/03/13.
//  Copyright (c) 2013 WaWa-YoDa. All rights reserved.
//

#include "engine.h"

static engine* currentInstance;


engine::engine(){
	futurX=0, futurY=0, futurZ=0;
    visionX = 0, visionY = 0, visionZ = 0;
    
    godX=0, godY=50, godZ=0;
    
    gravity = 15.0;
    
    vitesse = 0.25;
    state = 1;
    
    viewMode = 0; //0=FPS 1=fixed on 0:20:0 2=camera follow
    viewModePressed = false; //to only change one time until touche is relached
    
    contextInitialized = false;//display and other things
    
    keyboardInitialized = false;
    
	lastLeftClic = 0;
    lastRightClic = 0;
    reloadTime = 250;

	isSelecting = false; //selection picking mode
    
    
    selectedFace=0;
    
    centerX = 400;
    centerY = 300;
    
    centerMouse=0;
    
	mouseLeftClicked = false;
    mouseRightClicked = false;
   
}

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
    
    //centerX = glutGet(GLUT_WINDOW_WIDTH) / 2;
    //centerY = glutGet(GLUT_WINDOW_HEIGHT) / 2;
    
    // Permet d'exécuter le fonction maFonction en parallèle
    pthread_create(&thread, NULL, engine::run, NULL);

}

void* engine::run(void*){
	while(!currentInstance->contextInitialized){
		#ifdef _WIN32
		Sleep(1000);
        #else
		sleep(1.0);
        #endif
   
	}
     unsigned int startTime = glutGet(GLUT_ELAPSED_TIME);
    while (currentInstance->state > 0) {
        startTime =  glutGet(GLUT_ELAPSED_TIME);
        currentInstance->perform(currentInstance->session->getKeys(), currentInstance->session->getKeysUp(), currentInstance->session->getKeysDown());

        while((unsigned int) glutGet(GLUT_ELAPSED_TIME) < startTime+(1)){
            #ifdef _WIN32
			Sleep(1);
			#else
			sleep(0.01);
			#endif
        }
    }
    
    return NULL;
}


void engine::perform(Bool* key,Bool* keyUp,Bool* keyDown){
    
	
    unsigned int startTime = glutGet(GLUT_ELAPSED_TIME);
    
    //aField->time+=0.0001;
    if(aField->time>=24.0){
        aField->time = 0;
    }
    
    if(!keyboardInitialized){
        return;
    }
    
    if(mouseRightClicked){
        //lastRightClic = glutGet(GLUT_ELAPSED_TIME);
        
        chunk* c = NULL;
        
        if(pickedBloc[selectedBloc]!=NULL)
            c = pickedBloc[selectedBloc]->getChunk();
        else{
            cout << "don't know this bloc ..." << endl;
        }
        
        if(c!= NULL){
            
        if(selectedFace == 2){
            bloc* nBloc = c->getBloc(pickedBloc[selectedBloc]->positionX,pickedBloc[selectedBloc]->positionY+1,pickedBloc[selectedBloc]->positionZ);
            
            if(nBloc != NULL){
            *nBloc =  bloc(pickedBloc[selectedBloc]->positionX, pickedBloc[selectedBloc]->positionY+1, pickedBloc[selectedBloc]->positionZ, 0.0f, 0.9f, 0.05f, 0.05f, 1.0f);
            
            nBloc->setChunk(c);
            }
            
        }
        
        if(selectedFace == 4){
                bloc* nBloc = c->getBloc(pickedBloc[selectedBloc]->positionX,pickedBloc[selectedBloc]->positionY-1,pickedBloc[selectedBloc]->positionZ);
            
             if(nBloc != NULL){   
                *nBloc =  bloc(pickedBloc[selectedBloc]->positionX, pickedBloc[selectedBloc]->positionY-1, pickedBloc[selectedBloc]->positionZ, 0.0f, 0.9f, 0.05f, 0.05f, 1.0f);
            
                nBloc->setChunk(c);
             }
            
        }
        
        if(selectedFace == 5){
                bloc* nBloc = c->getBloc(pickedBloc[selectedBloc]->positionX,pickedBloc[selectedBloc]->positionY,pickedBloc[selectedBloc]->positionZ+1);
            
            if(nBloc != NULL){ 
                *nBloc =  bloc(pickedBloc[selectedBloc]->positionX, pickedBloc[selectedBloc]->positionY, pickedBloc[selectedBloc]->positionZ+1, 0.0f, 0.9f, 0.05f, 0.05f, 1.0f);
            
                nBloc->setChunk(c);
            }
            
        }
        
        if(selectedFace == 6){
                bloc* nBloc = c->getBloc(pickedBloc[selectedBloc]->positionX,pickedBloc[selectedBloc]->positionY,pickedBloc[selectedBloc]->positionZ-1);
            
            if(nBloc != NULL){
                *nBloc =  bloc(pickedBloc[selectedBloc]->positionX, pickedBloc[selectedBloc]->positionY, pickedBloc[selectedBloc]->positionZ-1, 0.0f, 0.9f, 0.05f, 0.05f, 1.0f);
            
                nBloc->setChunk(c);
            }
            
        }
        
        if(selectedFace == 1){
                bloc* nBloc = c->getBloc(pickedBloc[selectedBloc]->positionX-1,pickedBloc[selectedBloc]->positionY,pickedBloc[selectedBloc]->positionZ);
            
            if(nBloc != NULL){
                *nBloc =  bloc(pickedBloc[selectedBloc]->positionX-1, pickedBloc[selectedBloc]->positionY, pickedBloc[selectedBloc]->positionZ, 0.0f, 0.9f, 0.05f, 0.05f, 1.0f);
            
                nBloc->setChunk(c);
            }
            
        }
        
        if(selectedFace == 3){
                bloc* nBloc = c->getBloc(pickedBloc[selectedBloc]->positionX+1,pickedBloc[selectedBloc]->positionY,pickedBloc[selectedBloc]->positionZ);
            if(nBloc != NULL){
                *nBloc =  bloc(pickedBloc[selectedBloc]->positionX+1, pickedBloc[selectedBloc]->positionY, pickedBloc[selectedBloc]->positionZ, 0.0f, 0.9f, 0.05f, 0.05f, 1.0f);
            
                nBloc->setChunk(c);
            }
            
        }
        }else{
            cout << "don't know chunk of this bloc ..." << endl;
        }
        
    }
    
    if(mouseLeftClicked){
        
        bloc* blc = pickedBloc[selectedBloc];
        
        
        
        if(blc != NULL){
            
            
            chunk* orC = blc->getChunk();
            
            cout << blc->positionX << ":" << blc->positionY << ":" << blc->positionZ << ":" << endl;
            
            if(orC != NULL){
                vector<chunk*>* aL;
                chunk* aC;
                bloc*  aB;
                
                aL = aField->getNearestChunk(orC->positionX-1, orC->positionY, 0.4);
                for(unsigned int cpt=0; cpt< aL->size(); cpt++){
                    aC = aL->at(cpt);
                    if(aC!=NULL){
                        aB = aC->getBloc(blc->positionX-1,  blc->positionY,  blc->positionZ);
                        if(aB!=NULL) aB->visible = true;
                    }
                }
                
                aL = aField->getNearestChunk(orC->positionX+1, orC->positionY, 0.4);
                for(unsigned int cpt=0; cpt< aL->size(); cpt++){
                    aC = aL->at(cpt);
                    if(aC!=NULL){
                        aB = aC->getBloc(blc->positionX+1,  blc->positionY,  blc->positionZ);
                        if(aB!=NULL)aB->visible = true;
                    }
                }
                
                aL = aField->getNearestChunk(orC->positionX, orC->positionY, 0.4);
                for(unsigned int cpt=0; cpt< aL->size(); cpt++){
                    aC = aL->at(cpt);
                    if(aC!=NULL){
                        aB = aC->getBloc(blc->positionX,  blc->positionY-1,  blc->positionZ);
                        if(aB!=NULL)aB->visible = true;
                    }
                }
                
                aL = aField->getNearestChunk(orC->positionX, orC->positionY, 0.4);
                for(unsigned int cpt=0; cpt< aL->size(); cpt++){
                    aC = aL->at(cpt);
                    if(aC!=NULL){
                        aB = aC->getBloc(blc->positionX,  blc->positionY+1,  blc->positionZ);
                        if(aB!=NULL)aB->visible = true;
                    }
                }
                
                aL = aField->getNearestChunk(orC->positionX, orC->positionY-1, 0.4);
                for(unsigned int cpt=0; cpt< aL->size(); cpt++){
                    aC = aL->at(cpt);
                    if(aC!=NULL){
                        aB = aC->getBloc(blc->positionX,  blc->positionY,  blc->positionZ-1);
                        if(aB!=NULL)aB->visible = true;
                    }
                }
                
                aL = aField->getNearestChunk(orC->positionX, orC->positionY+1, 0.4);
                for(unsigned int cpt=0; cpt< aL->size(); cpt++){
                    aC = aL->at(cpt);
                    if(aC!=NULL){
                        aB = aC->getBloc(blc->positionX,  blc->positionY,  blc->positionZ+1);
                        if(aB!=NULL)aB->visible = true;
                    }
                }
            }
            
            *blc = bloc(0, blc->positionX, blc->positionY, blc->positionZ, 0.0);
            
        }
        
        
        mouseLeftClicked = false;
        
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
        futurX = player.positionX - (vitesse * 0.015f)*cos(player.angleVision)  *player.vitesse;
        futurZ = player.positionZ - (vitesse * 0.015f)*sin(player.angleVision)  *player.vitesse;
    }
    if( key[UP_ARROW]){
        
        
        futurX = player.positionX + ( vitesse * 0.020f)*cos(player.angleVision)  *player.vitesse;
        futurZ = player.positionZ + (vitesse * 0.020f)*sin(player.angleVision)  *player.vitesse;
    }
    
    futurY = (player.positionY-(0.001f*gravity));
    
    
    bool* col = collision::detectCollisions(aField, &player, futurX, futurY, futurZ);
    
    if(!col[1]){
        player.positionY = futurY;
        player.fall += (0.001f*gravity); //don't forget in jump to remove jumped size
    }else{
        if(player.fall > 3.0f){
            player.fight(player.fall-3.0f);
        }
        player.fall = 0.0f;
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
        player.angleVision -= 0.005f*vitesse *player.vitesse;
    }
    if( key[RIGHT_ARROW]){
        player.angleVision += 0.005f*vitesse *player.vitesse;
    }
    if (key[GLUT_KEY_PAGE_DOWN]){
        player.positionY -= 0.005f*vitesse *player.vitesse;
    }
    if( key[GLUT_KEY_PAGE_UP]){
        player.positionY += 0.005f*vitesse *player.vitesse;
    }
    
    
    if( !key['v'] && viewModePressed){
        viewModePressed = false;
    }
    if( key['v'] && !viewModePressed){
        viewMode = (viewMode+1)%3;
        viewModePressed = true;
    }
    
    if( key[' '] && player.jump==0){
        futurY = player.positionY-0.1f;
        bool* col = collision::detectCollisions(aField, &player, futurX, futurY, futurZ);
        if(col[1]){
          player.jump+=1.0f; //to start log at 1
        }
    }
    
    if(player.jump>0){
        player.jump+= 1*vitesse;
        player.jumped += 0.008f*log(player.jump) -(0.001f*gravity);
        
        futurY = player.positionY + 0.008f*log(player.jump);
        bool* col = collision::detectCollisions(aField, &player, player.positionX, futurY, player.positionZ);
        if(!col[1]){
            player.positionY = futurY;
            player.fall -=  0.008f*log(player.jump);
        }
        
        if(player.jumped>=player.jumpMax){
            player.jumped = 0.0f;
            player.jump = -1.0f;
        }
    }
    
    if( !key[' '] && player.jump == -1.0f){
        player.jump = 0.0f;
    }
    
    if( !key['z'])
       godX-=0.1f;
    if( !key['s'])
        godX+=0.1f;
    
    if( !key['a'])
        godY+=0.1f;
    if( !key['e'])
        godY-=0.1f;
    
    
    if( !key['q'])
        godZ+=0.1f;
    if( !key['d'])
        godZ-=0.1f;
    
    
       
    
    //player.angleVision += 0.0005f * (mouseY - centerY) *player.vitesse;
    
    //player.angleVision = fmod(player.angleVision, (2.0*3.14));
    //CameraAngle.y = -1.0f * (x - centerX);
    if(centerMouse == maxCenterMouse){
        centerMouse = 0;
        //glutWarpPointer(centerX, centerY);
    }else{
        centerMouse++;
    }
    
    
    while((unsigned int)glutGet(GLUT_ELAPSED_TIME) < startTime+(  (1/fps)*1000 )){
        #ifdef _WIN32
		Sleep(1000/60);
		#else
		sleep(1.0/60.0);
		#endif

    }

}



void engine::loadfield(string fileName){
    aField = new field("nothing yep");
}



void engine::simplePerform(Bool* key,Bool* keyUp,Bool* keyDown){
    if (key[DOWN_ARROW]){
        
        
        futurX = player.positionX - (vitesse * 0.015f)*cos(player.angleVision)  *player.vitesse;
        futurZ = player.positionZ - (vitesse * 0.015f)*sin(player.angleVision)  *player.vitesse;
        futurY = player.positionY;
        
        player.positionX = futurX;
        player.positionZ = futurZ;
        
    }
    if( key[UP_ARROW]){
        
        
        futurX = player.positionX + ( vitesse * 0.020f)*cos(player.angleVision)  *player.vitesse;
        futurZ = player.positionZ + (vitesse * 0.020f)*sin(player.angleVision)  *player.vitesse;
        futurY = player.positionY;
        
        player.positionX = futurX;
        player.positionZ = futurZ;
        
    }
    if (key[LEFT_ARROW]){
        player.angleVision -= 0.005f*vitesse *player.vitesse;
    }
    if( key[RIGHT_ARROW]){
        player.angleVision += 0.005f*vitesse *player.vitesse;
    }
}



