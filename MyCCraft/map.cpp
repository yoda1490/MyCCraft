//
//  map.cpp
//  MyCCraft
//
//  Created by WaWa-YoDa on 05/04/13.
//  Copyright (c) 2013 WaWa-YoDa. All rights reserved.
//

#include "map.h"

chunk* tmp = 0;

map::map(string aFolder){
    folder = aFolder;
    
    
    
    
    
    for(int x=0; x< 16; x++){
        for(int z=0; z< 16; z++){
            for(int y=0; y< 17; y++){
                bloc* aBloc = new bloc(x, y, z, 0.0, 0.2, 0.6, 0.2, 1.0);
                if(y<0 && x!=0 && x!=15 && z!=0 && z!=15)
                    aBloc->visible = false;
                listBloc.push_back(*aBloc);
            }
        }
    }
    
    for(int cpt=0; cpt<10; cpt++){
        listBloc.push_back(*new bloc(13.0, 17.0+cpt, 15.0-cpt, 90.0, 0.6, 0.2, (float)cpt/10.0, 1.0));
        listBloc.push_back(*new bloc(14.0, 17.0+cpt, 15.0-cpt, 90.0, 0.6, 0.2, (float)cpt/10.0, 1.0));
        listBloc.push_back(*new bloc(15.0, 17.0+cpt, 15.0-cpt, 90.0, 0.6, 0.2, (float)cpt/10.0, 1.0));
    }
    
    
    for(int cpt=0; cpt < 10; cpt++){
        listBloc.push_back(*new bloc(cpt+5.0, 17.0, 0.0, 0.0, 0.6, (float)cpt/10.0, 0.2, 1.0, 1.0));
        listBloc.push_back(*new bloc(cpt+5.0, 18.0, 0.0, 0.0, 0.6, (float)cpt/10.0, 0.2, 1.0, 1.0));
        listBloc.push_back(*new bloc(cpt+5.0, 19.0, 0.0, 0.0, 0.6, (float)cpt/10.0, 0.2, 1.0, 1.0));
        listBloc.push_back(*new bloc(cpt+5.0, 19.0, 1.0, 0.0, 0.6, (float)cpt/10.0, 0.2, 1.0, 1.0));
        listBloc.push_back(*new bloc(cpt+5.0, 19.0, 2.0, 0.0, 0.6, (float)cpt/10.0, 0.2, 1.0, 1.0));
        listBloc.push_back(*new bloc(cpt+5.0, 18.0, 2.0, 0.0, 0.6, (float)cpt/10.0, 0.2, 1.0, 1.0));
        listBloc.push_back(*new bloc(cpt+5.0, 17.0, 2.0, 0.0, 0.6, (float)cpt/10.0, 0.2, 1.0, 1.0));
    }
    
        
    /*
    chunk aChunk = *new chunk(0, 0,&listBloc);
    
    vector<chunk> listChunk;
    
    tmp = &aChunk;
    
    for(int cpt=0; cpt<32;cpt++){
        for(int cpt2=0; cpt2<32;cpt2++){
            listChunk.push_back(aChunk);
        }
    }
    
    
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


chunk* map::getNearestChunk(float x, float y){
    chunk* listChunk[9];
    
    for(int cpt=0; cpt<9; cpt++){
        //listChunk[cpt] = regions[0]->listChunk->at(cpt);
        listChunk[cpt] = tmp;
    }
    
    return (chunk*)listChunk;
}