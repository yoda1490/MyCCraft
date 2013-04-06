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
    
    
    
    if(futurX+aPerso->hitbox > aBloc->position[0]-aBloc->size/2
       && futurX-aPerso->hitbox < aBloc->position[0]+aBloc->size/2){
    
        if(aPerso->positionY+aPerso->tailleY > aBloc->position[1]-aBloc->size/2
           && aPerso->positionY+0.001 < aBloc->position[1]+aBloc->size/2){
                
                if(aPerso->positionZ+aPerso->hitbox > aBloc->position[2]-aBloc->size/2
                    && aPerso->positionZ-aPerso->hitbox < aBloc->position[2]+aBloc->size/2){
                    col[0] = true;
                }
        }
    }
    
    if(aPerso->positionX+aPerso->hitbox > aBloc->position[0]-aBloc->size/2
       && aPerso->positionX-aPerso->hitbox < aBloc->position[0]+aBloc->size/2){
        
        if(futurY+aPerso->tailleY > aBloc->position[1]-aBloc->size/2
           && futurY+0.001 < aBloc->position[1]+aBloc->size/2){
            
            if(aPerso->positionZ+aPerso->hitbox > aBloc->position[2]-aBloc->size/2
               && aPerso->positionZ-aPerso->hitbox < aBloc->position[2]+aBloc->size/2){
                col[1] = true;
            }
        }
    }
    
    if(aPerso->positionX+aPerso->hitbox > aBloc->position[0]-aBloc->size/2
       && aPerso->positionX-aPerso->hitbox < aBloc->position[0]+aBloc->size/2){
        
        if(aPerso->positionY+aPerso->tailleY > aBloc->position[1]-aBloc->size/2
           && aPerso->positionY+0.001 < aBloc->position[1]+aBloc->size/2){
            
            if(futurZ+aPerso->hitbox > aBloc->position[2]-aBloc->size/2
               && futurZ-aPerso->hitbox < aBloc->position[2]+aBloc->size/2){
                col[2] = true;
            }
        }
    }

    return col;
    
    
}

bool* collision::detectCollisions(vector<bloc>* listBloc, perso* aPerso, float futurX, float futurY, float futurZ){
    bool col[3] = {false, false, false};
    
    int posPerso = ((int)aPerso->positionX)*4096 + ((int)aPerso->positionY)*1 + ((int)aPerso->positionZ)*256;
    
    //cout << posPerso << endl;
    
    int rd = 3; //radius detection
    
    
    long unsigned end = posPerso + rd + rd*256 + rd*4096;
    if(end > listBloc->size()){
        end = listBloc->size();
    }
    
    for(int unsigned x=0;x<rd*2;x++){
        for(int unsigned z=0;z<rd*2;z++){
                for(int unsigned y=0;y<rd*2;y++){
                    
                    if(((int)aPerso->positionX)-rd+(int)x<0 || ((int)aPerso->positionX)-rd+x >15   ||
                       ((int)aPerso->positionY)-rd+(int)y<0 || ((int)aPerso->positionY)-rd+y > 256 ||
                       ((int)aPerso->positionZ)-rd+(int)z<0 || ((int)aPerso->positionZ)-rd+z > 15)
                        break;
                    
                    long int indexX = (((int)aPerso->positionX)-rd+x)*4096;
                    long int indexY = (((int)aPerso->positionY)-rd+y)*1;
                    long int indexZ = (((int)aPerso->positionZ)-rd+z)*256;
                    
                    
                    
                    long int index =  indexX+indexY+indexZ;
                    
                    
                    if(index <0 || index > listBloc->size())
                        break;
                    
                    
                    bool * colTmp = detectCollision(&(listBloc->at(index)), aPerso, futurX, futurY, futurZ);
                    if(colTmp[0]){
                            col[0] = true;
                        }
                    if(colTmp[1]){
                            col[1] = true;
                        }
                    if(colTmp[2]){
                            col[2] = true;
                        }
                    if(colTmp[0] && colTmp[1] && colTmp[2]){
                        return col;
                        }
                }
        }
        
    }
    
    return col;
}