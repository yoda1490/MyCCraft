//
//  Fun.cpp
//  MyCCraft
//
//  Created by WaWa-YoDa on 19/04/13.
//  Copyright (c) 2013 WaWa-YoDa. All rights reserved.
//

#include "Base.h"
using namespace std;

class Fun : public Base{
    
public:
    
    static chunk* generate(float x, float y){
        chunk* aChunk = new chunk(x,y);
        vector<bloc> listBloc;
        
        int height = 10;
        
        for(int x=0; x< 16; x++){
            cout << "-"; //to display progress while generating chunk
            for(int z=0; z< 16; z++){
                for(int y=0; y< 256; y++){
                    bloc* aBloc;
                    if(y<height){
                        aBloc = new bloc(1, x, y, z, 1.0);
                    }else{
                        aBloc = new air(0, x, y, z, 0.0);
                        aBloc->visible = false;
                    }
                    if(y<height-1)
                        aBloc->visible = false;
                    listBloc.push_back(*aBloc);
                }
            }
        }
        
        
        aChunk->setBlocs(&listBloc);
        
        
        for(int cpt=0; cpt<10; cpt++){
            aChunk->setBloc(new bloc(13.0, height+cpt, 15.0-cpt, 0.0, 0.6, 0.2, (float)cpt/10.0, 1.0));
            aChunk->setBloc(new bloc(14.0, height+cpt, 15.0-cpt, 0.0, 0.6, 0.2, (float)cpt/10.0, 1.0));
            aChunk->setBloc(new bloc(15.0, height+cpt, 15.0-cpt, 0.0, 0.6, 0.2, (float)cpt/10.0, 1.0));
        }
        
        
        for(int cpt=0; cpt < 10; cpt++){
            aChunk->setBloc(new bloc(cpt+5.0, height, 0.0, 0.0, 0.6, (float)cpt/10.0, 0.2, 1.0, 1.0));
            aChunk->setBloc(new bloc(cpt+5.0, height+1, 0.0, 0.0, 0.6, (float)cpt/10.0, 0.2, 1.0, 1.0));
            aChunk->setBloc(new bloc(cpt+5.0, height+2, 0.0, 0.0, 0.6, (float)cpt/10.0, 0.2, 1.0, 1.0));
            aChunk->setBloc(new bloc(cpt+5.0, height+2, 1.0, 0.0, 0.6, (float)cpt/10.0, 0.2, 1.0, 1.0));
            aChunk->setBloc(new bloc(cpt+5.0, height+2, 2.0, 0.0, 0.6, (float)cpt/10.0, 0.2, 1.0, 1.0));
            aChunk->setBloc(new bloc(cpt+5.0, height+1, 2.0, 0.0, 0.6, (float)cpt/10.0, 0.2, 1.0, 1.0));
            aChunk->setBloc(new bloc(cpt+5.0, height, 2.0, 0.0, 0.6, (float)cpt/10.0, 0.2, 1.0, 1.0));
        }
        
        
        return aChunk;
    }
};