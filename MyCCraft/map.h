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


using namespace std;


class map{
public:
  //contain a circular list of maximum 4 regions around the player
    //region regions[4];
    //int regionsName[4][2];
    
    region aRegion;
    
    
    string folder; //folder of this map;
    
    map(string aFolder);
    
    
    
    //load the 4nearest region
    void loadNearestRegion(float x, float y);
    
    //return a list of the 81 nearest chunk (grid 9*9) around the player
    chunk* getNearestChunk(float x, float y);
    
    
};

#endif /* defined(__MyCCraft__map__) */
