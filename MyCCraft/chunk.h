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

using namespace std;
//define a list of 16x16x256 bloc

class chunk{
private:
    vector<class bloc*> listBloc; //65536 blocs
public:
    float positionX, positionY; //should be multiple of 16
    
    
    
    chunk(const chunk &source); //copy constructor
    chunk(float x, float y);
    void setBlocs(vector<bloc*>* blocs);
    
    void setBloc(bloc* aBloc); //place a bloc at the right position in the vector
    bloc* getBloc(long int x,long int y,long int z);

    
    float * highestPos(float x, float z); //return the highest position of a solid bloc in x, y
    
    vector<bloc*>* getListBloc();
    
};

#endif /* defined(__MyCCraft__chunk__) */
