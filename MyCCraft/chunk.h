//
//  chunk.h
//  MyCCraft
//
//  Created by WaWa-YoDa on 05/04/13.
//  Copyright (c) 2013 WaWa-YoDa. All rights reserved.
//

#ifndef __MyCCraft__chunk__
#define __MyCCraft__chunk__

#include <iostream>
#include <vector>
#include "bloc.h"
#include "blocAir.h"

using namespace std;
//define a list of 16x16x256 bloc

class chunk{
public:
    float positionX=0, positionY=0; //should be multiple of 16
    vector<bloc> listBloc; //65536 blocs
    
    
    chunk(const chunk &source); //copy constructor
    chunk(float x, float y);
    void setBlocs(vector<bloc>* blocs);
    
    void setBloc(bloc* aBloc); //place a bloc at the right position in the vector
    
    float * highestPos(float x, float y); //return the highest position of a solid bloc in x, y
    
};

#endif /* defined(__MyCCraft__chunk__) */
