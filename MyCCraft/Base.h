//
//  Base.h
//  MyCCraft
//
//  Created by WaWa-YoDa on 19/04/13.
//  Copyright (c) 2013 WaWa-YoDa. All rights reserved.
//

#ifndef __MyCCraft__Base__
#define __MyCCraft__Base__

#include <iostream>
#include <vector>
#include "bloc.h"
#include "blocAir.h"

#include "chunk.h"

using namespace std;


//generate a plan chunk (can be directl use but better area derivate from this one)

class Base{
  
public:
    static chunk* generate(float x, float y);
};


#endif /* defined(__MyCCraft__Base__) */

