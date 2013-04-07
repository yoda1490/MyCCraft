//
//  map.h
//  MyCCraft
//
//  Created by WaWa-YoDa on 05/04/13.
//  Copyright (c) 2013 WaWa-YoDa. All rights reserved.
//

#ifndef __MyCCraft__map__
#define __MyCCraft__map__

#include <iostream>
#include "region.h"
#include <vector>
#include "chunkGenerator.h"

using namespace std;


class map{
public:
  //contain a circular list of maximum 4 regions around the player
    //region regions[4];
    //int regionsName[4][2];
    
    region aRegion;
    
    
    string folder; //folder of this map;
    
    map(string aFolder);
    
    
    //the current hour in this map (max 24, ex for 14h30 it will be 14.5)
    float time = 10;
    
    //load the 4nearest region
    void loadNearestRegion(float x, float y);
    
    
    
    //return a list nearest regions in a radius around the player
    region * getNearestRegion(float x, float y, float radius);
    //return a list nearest chunks in a radius around the player
    vector<chunk>* getNearestChunk(float x, float y, float radius);
    
    
};

#endif /* defined(__MyCCraft__map__) */
