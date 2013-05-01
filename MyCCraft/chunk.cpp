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
    
	//initialisation with air bloc everywhere
	cout << "*";
	for(int x=0; x< 16; x++){
        for(int z=0; z< 16; z++){
            for(int y=0; y< 256; y++){
                    listBloc.push_back(new bloc(0, (float)x, (float)y, (float)z, 0.0f));
            }
        }
    }
	
    
}


chunk::chunk(const chunk &source){
    positionX=source.positionX;
    positionY=source.positionY;
    
    for(unsigned int cpt=0; cpt<source.listBloc.size(); cpt++){
        listBloc.push_back(source.listBloc.at(cpt));
        listBloc.at(cpt)->setChunk(this);
    }
}


void chunk::setBlocs(vector<bloc*>* blocs){
    listBloc.clear();
    for(unsigned int cpt=0; cpt<blocs->size(); cpt++){
        listBloc.push_back(blocs->at(cpt));
        listBloc.at(cpt)->setChunk(this);
    }

}

void chunk::setBloc(bloc* aBloc){
    
    long int indexX = (((int)aBloc->positionX))*4096;
    long int indexY = (((int)aBloc->positionY));
    long int indexZ = (((int)aBloc->positionZ))*256;
    
    long int index =  indexX+indexY+indexZ;
    aBloc->setChunk(this);
    listBloc.at(index) = aBloc;
    
    
}

bloc* chunk::getBloc(long int x,long int y,long int z){
    long int indexX = (x)*4096;
    long int indexY = (y);
    long int indexZ = (z)*256;
    
    long int index =  (long int)indexX+(long int)indexY+(long int)indexZ;
    if(index>=0 && index<listBloc.size()){
        if(listBloc.at(index)->getChunk() == NULL)
            listBloc.at(index)->setChunk(this);
        
        return (listBloc.at(index));
    }
    else
        return NULL;
    
}

vector<bloc*>* chunk::getListBloc(){
    return  &listBloc;
}