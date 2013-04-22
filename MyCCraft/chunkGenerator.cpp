//
//  chunkGenerator.cpp
//  MyCCraft
//
//  Created by WaWa-YoDa on 07/04/13.
//  Copyright (c) 2013 WaWa-YoDa. All rights reserved.
//

#include "chunkGenerator.h"




chunk chunkGenerator::generate(string seed, float x, float y){
    
    int nbType = 3;
    
    int type =  rand() % nbType;
    
    switch (type)
    {
        case 0: {
            return *Base::generate(x, y);
        }
        case 1: {
            return *Fun::generate(x, y);
        }
        case 2: {
            return *Mountain::generate(x, y);
        }
    }
    
    return *Base::generate(x, y); //just in case of an problem
    
}