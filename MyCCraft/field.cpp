//
//  field.cpp
//  MyCCraft
//
//  Created by WaWa-YoDa on 05/04/13.
//  Copyright (c) 2013 WaWa-YoDa. All rights reserved.
//

#include "field.h"

chunk* tmp = 0;
static field* currentInstance;
static float chunkX;
static float chunkY;



field::field(string aFolder): folder(aFolder), aRegion(0,0), time(STARTTIME), generating(false){
    
    
    
    vector<chunk> listChunk;
    
    cout << "Generating field: [";
    for(int cpt=-2; cpt<=2;cpt++){
        for(int cpt2=-2; cpt2<=2;cpt2++){
            listChunk.push_back(*new chunk(chunkGenerator::generate("nothing yet", (float)cpt*16,(float)cpt2*16)));
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
void field::loadNearestRegion(float x, float y){
    //test si régions à chargé déjà chargé
    for(int cpt=0; cpt<4; cpt++){
        
    }
    
}


region* field::getNearestRegion(float x, float y, float radius){
    return &aRegion;
}

vector<chunk*>* field::getNearestChunk(float x, float y, float radius){
    
    
    vector<chunk*>* nearestChunk = new vector<chunk*>;
    //region* regTmp = getNearestRegion(x, y, radius);
    
    
    for(int cpt=(int)(x-radius-1.0f); cpt<=(int)(x+radius); cpt+=16){
        for(int cpt2=(int)(y-radius-1.0f); cpt2<=(int)(y+radius); cpt2+=16){
            chunk* tmp = aRegion.getChunk((float)cpt, (float)cpt2);
            if(tmp!= NULL){
                nearestChunk->push_back( tmp );
            }else{
                
                if(!generating){
                    
                    
                    chunkX = (float)cpt  -cpt %16;
                    chunkY = (float)cpt2 -cpt2%16;
                    
                    if(cpt < 0)
                        chunkX -=16;
                    
                    if(cpt2 < 0)
                        chunkY -=16;
                    
                    
                    pthread_t thread;
                    currentInstance = this;
                    pthread_create(&thread, NULL, generate, NULL);
   
                }
                
            }
        }
    }
    
    //return lstChunks;*/
    return nearestChunk;
}


vector<chunk*>* field::getNearestFrontChunk(float x, float y, float angleVision, float radius){
    float newX =(float) x + (radius/2.0f)*cos(angleVision) ;
    float newZ =(float) y + (radius/2.0f)*sin(angleVision) ;
    return getNearestChunk(newX, newZ, radius/2.0f);
}

void* field::generate(void *){
    if(!currentInstance->generating){
    currentInstance->generating = true;
    
    cout << "Generate: " << chunkX << ":" << chunkY << " [";
    chunk* tmpChk = new chunk(chunkGenerator::generate("nothing yet", chunkX,chunkY));
    //nearestChunk->push_back(tmpChk);
    
    
    currentInstance->aRegion.listChunk.push_back(*tmpChk);
    
    cout << "]  OK "  << endl;
    currentInstance->generating = false;
    }
    
    
    return NULL;
    
}