//
//  chunkGenerator.h
//  MyCCraft
//
//  Created by WaWa-YoDa on 07/04/13.
//  Copyright (c) 2013 WaWa-YoDa. All rights reserved.
//

#ifndef __MyCCraft__chunkGenerator__
#define __MyCCraft__chunkGenerator__

#include <iostream>
#include "chunk.h"
#include "Base.h"
#include "Fun.cpp"
#include "Mountain.cpp"

class chunkGenerator{
public:
    static chunk generate(string seed, float x, float y);
    
};

#endif /* defined(__MyCCraft__chunkGenerator__) */
