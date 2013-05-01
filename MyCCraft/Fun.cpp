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
        vector<bloc*> listBloc;
        
        int height = 10;
        
        for(int x=0; x< 16; x++){
            cout << "-"; //to display progress while generating chunk
            for(int z=0; z< 16; z++){
                for(int y=0; y< 256; y++){
                    bloc* aBloc;
                    if(y<height){
                        aBloc = new bloc(1, (float)x, (float)y, (float)z, 1.0f);
                    }else{
                        aBloc = new bloc(0, (float)x, (float)y, (float)z, 0.0f);
                        aBloc->visible = false;
                    }
                    if(y<height-1)
                        aBloc->visible = false;
                    listBloc.push_back(aBloc);
                }
            }
        }
        
        
        aChunk->setBlocs(&listBloc);
        
        
        for(int cpt=0; cpt<10; cpt++){
            aChunk->setBloc(new bloc(13.0f, (float)height+(float)cpt, (float)15.0f-(float)cpt, 0.0f, 0.6f, 0.2f, (float)cpt/10.0f, 1.0f));
            aChunk->setBloc(new bloc(14.0f, (float)height+(float)cpt, (float)15.0f-(float)cpt, 0.0f, 0.6f, 0.2f, (float)cpt/10.0f, 1.0f));
            aChunk->setBloc(new bloc(15.0f, (float)height+(float)cpt, (float)15.0f-(float)cpt, 0.0f, 0.6f, 0.2f, (float)cpt/10.0f, 1.0f));
        }
        
        
        for(int cpt=0; cpt < 10; cpt++){
            aChunk->setBloc(new bloc((float)cpt+5.0f, (float)height, 0.0f, 0.0f, 0.6f, (float)cpt/10.0f, 0.2f, 1.0f, 1.0f));
            aChunk->setBloc(new bloc((float)cpt+5.0f, (float)height+1.0f, 0.0f, 0.0f, 0.6f, (float)cpt/10.0f, 0.2f, 1.0f, 1.0f));
            aChunk->setBloc(new bloc((float)cpt+5.0f, (float)height+2.0f, 0.0f, 0.0f, 0.6f, (float)cpt/10.0f, 0.2f, 1.0f, 1.0f));
            aChunk->setBloc(new bloc((float)cpt+5.0f, (float)height+2.0f, 1.0f, 0.0f, 0.6f, (float)cpt/10.0f, 0.2f, 1.0f, 1.0f));
            aChunk->setBloc(new bloc((float)cpt+5.0f, (float)height+2.0f, 2.0f, 0.0f, 0.6f, (float)cpt/10.0f, 0.2f, 1.0f, 1.0f));
            aChunk->setBloc(new bloc((float)cpt+5.0f, (float)height+1.0f, 2.0f, 0.0f, 0.6f, (float)cpt/10.0f, 0.2f, 1.0f, 1.0f));
            aChunk->setBloc(new bloc((float)cpt+5.0f, (float)height, 2.0f, 0.0f, 0.6f, (float)cpt/10.0f, 0.2f, 1.0f, 1.0f));
        }
        
        
        return aChunk;
    }
};