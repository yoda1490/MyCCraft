//
//  chunk.cpp
//  MyCCraft
//
//  Created by WaWa-YoDa on 05/04/13.
//  Copyright (c) 2013 WaWa-YoDa. All rights reserved.
//

#include "chunk.h"


chunk::chunk(float x, float y, vector<bloc>* blocs){
    
    positionX = x;
    positionY = y;
    
    for(int cpt=0; cpt<blocs->size(); cpt++){
        listBloc.push_back(blocs->at(cpt));
    }

}