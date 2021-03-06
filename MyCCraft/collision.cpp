//
//  collision.cpp
//  MyCCraft
//
//  Created by WaWa-YoDa on 03/04/13.
//  Copyright (c) 2013 WaWa-YoDa. All rights reserved.
//

#include "collision.h"


bool* collision::detectCollision(bloc* aBloc, perso* aPerso, float x, float y , float z, float futurX, float futurY, float futurZ){
    
    bool* col = new bool[3];
	col[0] = false;
    col[1] = false;
	col[2] = false;

	if(aBloc == NULL)
		return col;

	if( aBloc->idBloc == 0)
		return col;
    
    if(futurX+aPerso->hitbox > aBloc->positionX-aBloc->size/2
       && futurX-aPerso->hitbox < aBloc->positionX+aBloc->size/2){
        
        if(y+aPerso->tailleY > aBloc->positionY-aBloc->size/2
           && y+0.001 < aBloc->positionY+aBloc->size/2){
            
            if(z+aPerso->hitbox > aBloc->positionZ-aBloc->size/2
               && z-aPerso->hitbox < aBloc->positionZ+aBloc->size/2){
                col[0] = true;
            }
        }
    }
    
    if(x+aPerso->hitbox > aBloc->positionX-aBloc->size/2
       && x-aPerso->hitbox < aBloc->positionX+aBloc->size/2){
        
        if(futurY+aPerso->tailleY    > aBloc->positionY-aBloc->size/2
           && futurY                  < aBloc->positionY+aBloc->size/2
           ){
            
            if(z+aPerso->hitbox > aBloc->positionZ-aBloc->size/2
               && z-aPerso->hitbox < aBloc->positionZ+aBloc->size/2){
                col[1] = true;
            }
        }
    }
    
    if(x+aPerso->hitbox > aBloc->positionX-aBloc->size/2
       && x-aPerso->hitbox < aBloc->positionX+aBloc->size/2){
        
        if(y+aPerso->tailleY > aBloc->positionY-aBloc->size/2
           && y+0.001 < aBloc->positionY+aBloc->size/2){
            
            if(futurZ+aPerso->hitbox > aBloc->positionZ-aBloc->size/2
               && futurZ-aPerso->hitbox < aBloc->positionZ+aBloc->size/2){
                col[2] = true;
            }
        }
    }
    
    return col;
}

bool* collision::detectCollisions(field* afield, perso* aPerso, float futurX, float futurY, float futurZ, int rd){
    
    vector<chunk*>* listChunk = afield->getNearestChunk(futurX, futurZ, 16);
    
    bool* col = new bool[3];
	col[0] = false;
    col[1] = false;
	col[2] = false;
    
    for(unsigned int cpt=0; cpt<listChunk->size();cpt++){
        
        float xf = futurX - listChunk->at(cpt)->positionX - afield->aRegion.positionX;
        float zf = futurZ - listChunk->at(cpt)->positionY - afield->aRegion.positionY;
        
        
        float x = aPerso->positionX - listChunk->at(cpt)->positionX - afield->aRegion.positionX;
        float z = aPerso->positionZ - listChunk->at(cpt)->positionY - afield->aRegion.positionY;
                
        bool * colTmp = detectCollisions(listChunk->at(cpt)->getListBloc(), aPerso, x, aPerso->positionY, z, xf, futurY, zf, rd);
        
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
    
    return col;
    
}

bool* collision::detectCollisions(vector<bloc*>* listBloc, perso* aPerso, float x, float y, float z, float futurX, float futurY, float futurZ, int rd){
    bool* col = new bool[3];
	col[0] = false;
    col[1] = false;
	col[2] = false;

	if(listBloc->size() <= 0){
		col[0] = true;
		col[1] = true;
		col[2] = true;
	}

    int posPerso = ((int)x)*4096 + ((int)y)*1 + ((int)z)*256;
    
    //cout << posPerso << endl;
    
    
    
    
    long unsigned end = posPerso + rd + rd*256 + rd*4096;
    if(end > listBloc->size()){
        end = listBloc->size();
    }
    
    for(int xt=0;xt<rd*2;xt++){
        for(int zt=0;zt<rd*2;zt++){
                for(int yt=0;yt<rd*2;yt++){
                    
                    if(((int)x)-rd+(int)xt<0 || ((int)x)-rd+xt >15   ||
                       ((int)y)-rd+(int)yt<0 || ((int)y)-rd+yt > 256 ||
                       ((int)z)-rd+(int)zt<0 || ((int)z)-rd+zt > 15)
                        break;
                    
                    
                    
                    long int indexX = (((int)x)-rd+xt)*4096;
                    long int indexY = (((int)y)-rd+yt)*1;
                    long int indexZ = (((int)z)-rd+zt)*256;
                    
                    
                    
                    unsigned int index =  indexX+indexY+indexZ;
                    
                    
                    if(index <0 || index > listBloc->size())
                        break;
                    
                    
                    
                    
                    bool * colTmp = (detectCollision(listBloc->at(index), aPerso, x, y, z, futurX, futurY, futurZ));
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