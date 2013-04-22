//
//  Base.cpp
//  MyCCraft
//
//  Created by WaWa-YoDa on 19/04/13.
//  Copyright (c) 2013 WaWa-YoDa. All rights reserved.
//

#include "Base.h"


chunk* Base::generate(float x, float y){
    chunk* aChunk = new chunk(x,y);
    vector<bloc> listBloc;
    
    int height = 10;
    
    for(int x=0; x< 16; x++){
        cout << "-"; //to display progressing generating chunk
        for(int z=0; z< 16; z++){
            for(int y=0; y< 256; y++){
                bloc* aBloc;
                if(y<height){
                    aBloc = new bloc(1, x, y, z, 1.0);
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
    
    
    aChunk->setBlocs(&listBloc);
    
    
    
    
    
    return aChunk;
}