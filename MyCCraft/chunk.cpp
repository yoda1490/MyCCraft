//
//  chunk.cpp
//  MyCCraft
//
//  Created by WaWa-YoDa on 05/04/13.
//  Copyright (c) 2013 WaWa-YoDa. All rights reserved.
//

#include "chunk.h"


chunk::chunk(float x, float y){
    
    positionX = x;
    positionY = y;
    
    
}


chunk::chunk(const chunk &source){
    positionX=source.positionX;
    positionY=source.positionY;
    
    for(int cpt=0; cpt<source.listBloc.size(); cpt++){
        listBloc.push_back(source.listBloc.at(cpt));
    }
}


void chunk::setBlocs(vector<bloc>* blocs){
    listBloc.clear();
    for(int cpt=0; cpt<blocs->size(); cpt++){
        listBloc.push_back(blocs->at(cpt));
    }

}

void chunk::setBloc(bloc* aBloc){
    
    long int indexX = (((int)aBloc->position[0]))*4096;
    long int indexY = (((int)aBloc->position[1]))*1;
    long int indexZ = (((int)aBloc->position[2]))*256;
    
    long int index =  indexX+indexY+indexZ;
    listBloc.at(index) = *aBloc;
    
}