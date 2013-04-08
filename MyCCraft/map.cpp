//
//  map.cpp
//  MyCCraft
//
//  Created by WaWa-YoDa on 05/04/13.
//  Copyright (c) 2013 WaWa-YoDa. All rights reserved.
//

#include "map.h"

chunk* tmp = 0;

map::map(string aFolder): folder(aFolder), aRegion(0,0){
    
    
    
    vector<chunk> listChunk;
    
    
    for(int cpt=-2; cpt<2;cpt++){
        for(int cpt2=-2; cpt2<2;cpt2++){
            listChunk.push_back(chunkGenerator::generate("nothing yet", cpt*16,cpt2*16));
        }
    }
    
    
    
    aRegion.setChunk(&listChunk);
    
    /*
    region* aRegion = new region(0,0,&listChunk);
    
    
    regions[0] = aRegion;
    regions[1] = aRegion;
    regions[2] = aRegion;
    regions[3] = aRegion;
    */
    
    
}


//todo
//load the 4 nearest region
void map::loadNearestRegion(float x, float y){
    //test si régions à chargé déjà chargé
    for(int cpt=0; cpt<4; cpt++){
        
    }
    
}


region* map::getNearestRegion(float x, float y, float radius){
    return &aRegion;
}

vector<chunk>* map::getNearestChunk(float x, float y, float radius){
    //need to be implemented with references and not copy of object !!!
    /**
     vector<chunk>* chunksTmp = new vector<chunk>;
    region* regTmp = getNearestRegion(x, y, radius);
    
    for(int cpt = -radius; cpt < radius; cpt++){
        for(int cpt2 = -radius; cpt2 < radius; cpt++){
            if(cpt >= 0 && cpt2 >= 0 && (cpt+16*cpt2) < regTmp->listChunk.size())
                chunksTmp->push_back(regTmp->listChunk.at(cpt+16*cpt2));
        }
    }
    return chunksTmp;
     **/
    return &(aRegion.listChunk);
}