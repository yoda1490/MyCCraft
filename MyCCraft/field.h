//
//  field.h
//  MyCCraft
//
//  Created by WaWa-YoDa on 05/04/13.
//  Copyright (c) 2013 WaWa-YoDa. All rights reserved.
//

#ifndef __MyCCraft__field__
#define __MyCCraft__field__

#include <iostream>
#include "region.h"
#include <vector>
#include "chunkGenerator.h"
#include <pthread.h>

using namespace std;

static float STARTTIME = 10;

class field{
public:
  //contain a circular list of maximum 4 regions around the player
    //region regions[4];
    //int regionsName[4][2];
    
    region aRegion;
    
    bool generating; //to allow only one generation simultaneously
    
    string folder; //folder of this field;
    
    field(string aFolder);
    
    
    //the current hour in this field (max 24, ex for 14h30 it will be 14.5)
    float time;

	field();
    
    //load the 4nearest region
    void loadNearestRegion(float x, float y);
    
    
    
    //return a list nearest regions in a radius around the player
    region * getNearestRegion(float x, float y, float radius);
    //return a list nearest chunks in a radius around the player
    vector<chunk*>* getNearestChunk(float x, float y, float radius);
    vector<chunk*>* getNearestFrontChunk(float x, float y, float angleVision, float radius); //only chunk behind the player
    
    static void* generate(void *); //launch a thread to generate missing chunk
    
    
};

#endif /* defined(__MyCCraft__field__) */
