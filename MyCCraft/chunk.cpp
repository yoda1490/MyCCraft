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
        listBloc.at(cpt).setChunk(this);
    }
}


void chunk::setBlocs(vector<bloc>* blocs){
    listBloc.clear();
    for(int cpt=0; cpt<blocs->size(); cpt++){
        listBloc.push_back(blocs->at(cpt));
        listBloc.at(cpt).setChunk(this);
    }

}

void chunk::setBloc(bloc* aBloc){
    
    long int indexX = (((int)aBloc->positionX))*4096;
    long int indexY = (((int)aBloc->positionY))*1;
    long int indexZ = (((int)aBloc->positionZ))*256;
    
    long int index =  indexX+indexY+indexZ;
    listBloc.at(index) = *aBloc;
    listBloc.at(index).setChunk(this);
    
}

bloc* chunk::getBloc(float x,float y,float z){
    
    long int indexX = (x)*4096;
    long int indexY = (y)*1;
    long int indexZ = (z)*256;
    
    long int index =  indexX+indexY+indexZ;
    if(index>=0 && index<listBloc.size())
        return &(listBloc.at(index));
    else
        return NULL;
    
}