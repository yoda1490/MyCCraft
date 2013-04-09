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
    
    cout << "Generating map: [";
    for(int cpt=-2; cpt<=2;cpt++){
        for(int cpt2=-2; cpt2<=2;cpt2++){
            listChunk.push_back(*new chunk(chunkGenerator::generate("nothing yet", cpt*16,cpt2*16)));
        }
    }
    
    cout << "] OK" << endl;
    
    
    
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

vector<chunk*>* map::getNearestChunk(float x, float y, float radius){
    
    
    vector<chunk*>* nearestChunk = new vector<chunk*>;
    //region* regTmp = getNearestRegion(x, y, radius);
    
    
    for(int cpt=x-radius-1; cpt<=x+radius; cpt+=16){
        for(int cpt2=y-radius-1; cpt2<=y+radius; cpt2+=16){
            chunk* tmp = aRegion.getChunk(cpt, cpt2);
            if(tmp!= NULL){
                nearestChunk->push_back( tmp );
            }else{
                
                if(!generating){
                    generating = true;
                    float chunkX = cpt  -cpt %16;
                    float chunkY = cpt2 -cpt2%16;
                    
                    if(cpt < 0)
                        chunkX -=16;
                    
                    if(cpt2 < 0)
                        chunkY -=16;
                    
                    
                    cout << cpt << ":" << cpt2 << "Generate: " << chunkX << ":" << chunkY << " [";
                    chunk* tmpChk = new chunk(chunkGenerator::generate("nothing yet", chunkX,chunkY));
                    nearestChunk->push_back(tmpChk);
                    aRegion.listChunk.push_back(*tmpChk);
                    cout << "]  OK "  << endl;
                    generating = false;
                }
                
            }
        }
    }
    
    //return lstChunks;*/
    return nearestChunk;
}