//
//  region.h
//  MyCCraft
//
//  Created by WaWa-YoDa on 05/04/13.
//  Copyright (c) 2013 WaWa-YoDa. All rights reserved.
//

#ifndef __MyCCraft__region__
#define __MyCCraft__region__

#include <iostream>
#include <vector>
#include "chunk.h"

using namespace std;

//define groups of 32×32 chunks
class region{
public:
    float positionX=0, positionY=0; //should be a multiple of 16x32=512
    vector<chunk> listChunk;
    
    
    
    
    region(float x, float y);
    
    
    void setChunk(vector<chunk>* chunks);
    
    chunk* getChunk(float x, float y); //return the chunk to the position x:z

};


#endif /* defined(__MyCCraft__region__) */
