//
//  region.cpp
//  MyCCraft
//
//  Created by WaWa-YoDa on 05/04/13.
//  Copyright (c) 2013 WaWa-YoDa. All rights reserved.
//

#include "region.h"


region::region(float x, float y){
    positionX = x;
    positionY = y;
    
    
}

void region::setChunk(vector<chunk>* chunks){
    for(int cpt=0; cpt<chunks->size(); cpt++){
        listChunk.push_back(chunks->at(cpt));
    }
}


//todo
chunk* region::getChunk(float x, float y){
    for(int cpt=0; cpt<listChunk.size();cpt++){
        if(x>=listChunk.at(cpt).positionX && x<listChunk.at(cpt).positionX+16.0 &&
           y>=listChunk.at(cpt).positionY && y<listChunk.at(cpt).positionY+16.0)
            return &listChunk.at(cpt);
    }
    return NULL;
}