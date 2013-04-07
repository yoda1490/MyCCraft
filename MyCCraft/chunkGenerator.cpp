//
//  chunkGenerator.cpp
//  MyCCraft
//
//  Created by WaWa-YoDa on 07/04/13.
//  Copyright (c) 2013 WaWa-YoDa. All rights reserved.
//

#include "chunkGenerator.h"


chunk chunkGenerator::generate(string seed, float x, float y){
    
    
    chunk aChunk = chunk(x,y);
    vector<bloc> listBloc;
    
    int height = 10;
    
    for(int x=0; x< 16; x++){
        for(int z=0; z< 16; z++){
            for(int y=0; y< 256; y++){
                bloc* aBloc;
                if(y<height){
                    aBloc = new bloc(x, y, z, 0.0, 0.2, 0.6, 0.2, 1.0);
                }else{
                    aBloc = new air(0, x, y, z, 0.0);
                    aBloc->visible = false;
                }
                if(y<height-1 && x!=0 && x!=15 && z!=0 && z!=15)
                    aBloc->visible = false;
                listBloc.push_back(*aBloc);
            }
        }
    }
    
    
    aChunk.setBlocs(&listBloc);
    
    
    for(int cpt=0; cpt<10; cpt++){
        aChunk.setBloc(new bloc(13.0, height+cpt, 15.0-cpt, 90.0, 0.6, 0.2, (float)cpt/10.0, 1.0));
        aChunk.setBloc(new bloc(14.0, height+cpt, 15.0-cpt, 90.0, 0.6, 0.2, (float)cpt/10.0, 1.0));
        aChunk.setBloc(new bloc(15.0, height+cpt, 15.0-cpt, 90.0, 0.6, 0.2, (float)cpt/10.0, 1.0));
    }
    
    
    for(int cpt=0; cpt < 10; cpt++){
        aChunk.setBloc(new bloc(cpt+5.0, height, 0.0, 0.0, 0.6, (float)cpt/10.0, 0.2, 1.0, 1.0));
        aChunk.setBloc(new bloc(cpt+5.0, height+1, 0.0, 0.0, 0.6, (float)cpt/10.0, 0.2, 1.0, 1.0));
        aChunk.setBloc(new bloc(cpt+5.0, height+2, 0.0, 0.0, 0.6, (float)cpt/10.0, 0.2, 1.0, 1.0));
        aChunk.setBloc(new bloc(cpt+5.0, height+2, 1.0, 0.0, 0.6, (float)cpt/10.0, 0.2, 1.0, 1.0));
        aChunk.setBloc(new bloc(cpt+5.0, height+2, 2.0, 0.0, 0.6, (float)cpt/10.0, 0.2, 1.0, 1.0));
        aChunk.setBloc(new bloc(cpt+5.0, height+1, 2.0, 0.0, 0.6, (float)cpt/10.0, 0.2, 1.0, 1.0));
        aChunk.setBloc(new bloc(cpt+5.0, height, 2.0, 0.0, 0.6, (float)cpt/10.0, 0.2, 1.0, 1.0));
    }
    
    
    return aChunk;
}