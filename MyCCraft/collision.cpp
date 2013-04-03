//
//  collision.cpp
//  MyCCraft
//
//  Created by WaWa-YoDa on 03/04/13.
//  Copyright (c) 2013 WaWa-YoDa. All rights reserved.
//

#include "collision.h"


bool* collision::detectCollision(bloc* aBloc, perso* aPerso, float futurX, float futurY, float futurZ){
    
    bool col[3] = {false, false, false};
    
    if(futurX > aBloc->position[0]-aBloc->size/2
       && futurX < aBloc->position[0]+aBloc->size/2){
    
        if(aPerso->positionY > aBloc->position[1]-aBloc->size/2
           && aPerso->positionY < aBloc->position[1]+aBloc->size/2){
                
                if(aPerso->positionZ > aBloc->position[2]-aBloc->size/2
                    && aPerso->positionZ < aBloc->position[2]+aBloc->size/2){
                    col[0] = true;
                }
        }
    }
    
    if(aPerso->positionX > aBloc->position[0]-aBloc->size/2
       && aPerso->positionX < aBloc->position[0]+aBloc->size/2){
        
        if(futurY > aBloc->position[1]-aBloc->size/2
           && futurY < aBloc->position[1]+aBloc->size/2){
            
            if(aPerso->positionZ > aBloc->position[2]-aBloc->size/2
               && aPerso->positionZ < aBloc->position[2]+aBloc->size/2){
                col[1] = true;
            }
        }
    }
    
    if(aPerso->positionX > aBloc->position[0]-aBloc->size/2
       && aPerso->positionX < aBloc->position[0]+aBloc->size/2){
        
        if(aPerso->positionY > aBloc->position[1]-aBloc->size/2
           && aPerso->positionY < aBloc->position[1]+aBloc->size/2){
            
            if(futurZ > aBloc->position[2]-aBloc->size/2
               && futurZ < aBloc->position[2]+aBloc->size/2){
                col[2] = true;
            }
        }
    }

    return col;
    
    
}

bool* collision::detectCollisions(vector<bloc*>* listBloc, perso* aPerso, float futurX, float futurY, float futurZ){
    bool col[3] = {false, false, false};
    for(int unsigned i=0;i<(*listBloc).size();i++){
        bool * colTmp = detectCollision((*listBloc)[i], aPerso, futurX, futurY, futurZ);
        if(colTmp[0]){
            col[0] = true;
        }
        if(colTmp[1]){
            col[1] = true;
        }
        if(colTmp[1]){
            col[1] = true;
        }
        if(colTmp[0] && colTmp[1] && colTmp[2]){
            return col;
        }
        
    }

    return col;
}