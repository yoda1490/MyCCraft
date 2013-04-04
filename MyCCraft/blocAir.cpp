//
//  blocAir.cpp
//  MyCCraft
//
//  Created by WaWa-YoDa on 04/04/13.
//  Copyright (c) 2013 WaWa-YoDa. All rights reserved.
//

#include "blocAir.h"

air::air(int idBloc, float x, float y, float z, float orientation):bloc(idBloc, x, y, z, orientation)
{
    
}

void air::draw(bool selected){
    //nothing to draw, used just to redefine bloc method
}