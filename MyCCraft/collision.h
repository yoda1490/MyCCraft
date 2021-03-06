//
//  collision.h
//  MyCCraft
//
//  Created by WaWa-YoDa on 03/04/13.
//  Copyright (c) 2013 WaWa-YoDa. All rights reserved.
//

#ifndef __MyCCraft__collision__
#define __MyCCraft__collision__

#include <iostream>
#include "bloc.h"
#include "perso.h"
#include "field.h"
#include <vector>

class collision{
public:
    static bool* detectCollisions(field* afield, perso* aPerso, float futurX, float futurY, float futurZ, int rd=4);
private:
    static bool* detectCollision(bloc* aBloc, perso* aPerso, float x, float y, float z, float futurX, float futurY, float futurZ);
    static bool* detectCollisions(vector<bloc*>* listBloc, perso* aPerso, float x, float y, float z, float futurX, float futurY, float futurZ, int rd=4);

    
};

#endif /* defined(__MyCCraft__collision__) */
