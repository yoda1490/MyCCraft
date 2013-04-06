//
//  region.cpp
//  MyCCraft
//
//  Created by WaWa-YoDa on 05/04/13.
//  Copyright (c) 2013 WaWa-YoDa. All rights reserved.
//

#include "region.h"


region::region(float x, float y,  vector<chunk>* chunks){
    positionX = x;
    positionY = y;
    
    for(int cpt=0; cpt<chunks->size(); cpt++){
        listChunk.push_back(chunks->at(cpt));
    }
}


//todo
vector<chunk>* region::getNearestChunk(float x, float y, int* nbChunk){
    *nbChunk = 81;
    
    
    return &listChunk;
}