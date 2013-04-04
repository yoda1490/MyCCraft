//
//  blocAir.h
//  MyCCraft
//
//  Created by WaWa-YoDa on 04/04/13.
//  Copyright (c) 2013 WaWa-YoDa. All rights reserved.
//

#ifndef __MyCCraft__blocAir__
#define __MyCCraft__blocAir__

#include <iostream>
#include "bloc.h"

class air : public bloc{
public:
    air(int idBloc, float x, float y, float z, float orientation);
    void draw(bool selected);
    
};

#endif /* defined(__MyCCraft__blocAir__) */
