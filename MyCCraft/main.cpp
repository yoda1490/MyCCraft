//
//  main.cpp
//  MyCCraft
//
//  Created by WaWa-YoDa on 27/03/13.
//  Copyright (c) 2013 WaWa-YoDa. All rights reserved.
//

#include <iostream>
#include "OpenGLSetup.h"
#include "scene.h"

int main(int argc, char ** argv)
{
    
    scene theGame;
    OpenGLSetup session("MyCCraft", &theGame, 800, 600);
    
    session.setupWindow(&argc, argv);
    
    
    
    return 0;
}

