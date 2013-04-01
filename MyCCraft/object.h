//
//  object.h
//  MyCCraft
//
//  Created by WaWa-YoDa on 28/03/13.
//  Copyright (c) 2013 WaWa-YoDa. All rights reserved.
//

#ifndef __MyCCraft__object__
#define __MyCCraft__object__

#include <iostream>

class object{
    float position[3];
    
    object();
    
    virtual void light() = 0;
    virtual void draw() = 0;
    object(float positionX, float positionY, float positionZ, float orientation);
};

#endif /* defined(__MyCCraft__object__) */
