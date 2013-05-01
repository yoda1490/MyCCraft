//
//  Fun.cpp
//  MyCCraft
//
//  Created by WaWa-YoDa on 19/04/13.
//  Copyright (c) 2013 WaWa-YoDa. All rights reserved.
//

#include "Base.h"
using namespace std;

class Mountain : public Base{
    
public:
    
    static chunk* generate(float x, float y){
        chunk* aChunk = new chunk(x,y);
        vector<bloc> listBloc;
        
        int height = 10;
        
        for(int x=0; x< 16; x++){
            cout << "-"; //to display progressing generating chunk
            for(int z=0; z< 16; z++){
                for(int y=0; y< 256; y++){
                    bloc* aBloc;
                    if(y<height){
                        aBloc = new bloc(1, (float)x, (float)y, (float)z, 1.0);
                    }else{
                        aBloc = new air(0, (float)x, (float)y, (float)z, 0.0);
                        aBloc->visible = false;
                    }
                    if(y<height-1)
                        aBloc->visible = false;
                    listBloc.push_back(*aBloc);
                }
            }
        }
        
        
        aChunk->setBlocs(&listBloc);
        
        
        for(int cpt=1; cpt<8; cpt++){
            for(int cpt2=1; cpt2<8; cpt2++){
                aChunk->setBloc(new bloc((float)cpt, (float)height+cpt+cpt2-10, (float)cpt2, 0.0f, 0.6f, (float)cpt2/10.0f, (float)cpt/10.0f, 1.0f));
                aChunk->setBloc(new bloc((float)cpt, (float)height+cpt+cpt2-10, (float)cpt2, 0.0f, 0.6f, (float)cpt2/10.0f, (float)cpt/10.0f, 1.0f));
                aChunk->setBloc(new bloc((float)cpt, (float)height+cpt+cpt2-10, (float)cpt2, 0.0f, 0.6f, (float)cpt2/10.0f, (float)cpt/10.0f, 1.0f));
            }
        }
        
        for(int cpt=14; cpt>=8; cpt--){
            for(int cpt2=14; cpt2>=8; cpt2--){
                aChunk->setBloc(new bloc((float)cpt, (float)40-height-cpt-cpt2, (float)cpt2, 0.0f, 0.6f, (float)cpt2/10.0f, (float)cpt/10.0f, 1.0f));
                aChunk->setBloc(new bloc((float)cpt, (float)40-height-cpt-cpt2, (float)cpt2, 0.0f, 0.6f, (float)cpt2/10.0f, (float)cpt/10.0f, 1.0f));
                aChunk->setBloc(new bloc((float)cpt, (float)40-height-cpt-cpt2, (float)cpt2, 0.0f, 0.6f, (float)cpt2/10.0f, (float)cpt/10.0f, 1.0f));
            }
        }
        
        for(int cpt=14; cpt>=8; cpt--){
            for(int cpt2=1; cpt2<8; cpt2++){
                aChunk->setBloc(new bloc((float)cpt, (float)25-height-cpt+cpt2, (float)cpt2, 0.0f, 0.6f, (float)cpt2/10.0f, (float)cpt/10.0f, 1.0f));
                aChunk->setBloc(new bloc((float)cpt, (float)25-height-cpt+cpt2, (float)cpt2, 0.0f, 0.6f, (float)cpt2/10.0f, (float)cpt/10.0f, 1.0f));
                aChunk->setBloc(new bloc((float)cpt, (float)25-height-cpt+cpt2, (float)cpt2, 0.0f, 0.6f, (float)cpt2/10.0f, (float)cpt/10.0f, 1.0f));
            }
        }
        
        for(int cpt=1; cpt<8; cpt++){
            for(int cpt2=14; cpt2>=8; cpt2--){
                aChunk->setBloc(new bloc((float)cpt, (float)25-height+cpt-cpt2, (float)cpt2, 0.0f, 0.6f, (float)cpt2/10.0f, (float)cpt/10.0f, 1.0f));
                aChunk->setBloc(new bloc((float)cpt, (float)25-height+cpt-cpt2, (float)cpt2, 0.0f, 0.6f, (float)cpt2/10.0f, (float)cpt/10.0f, 1.0f));
                aChunk->setBloc(new bloc((float)cpt, (float)25-height+cpt-cpt2, (float)cpt2, 0.0f, 0.6f, (float)cpt2/10.0f, (float)cpt/10.0f, 1.0f));
            }
        }

        
        
        
        
        
        return aChunk;
    }
};