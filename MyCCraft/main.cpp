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
#include "engine.h"

using namespace std;

int main(int argc, char ** argv)
{
    
    engine engine;
    scene theGame(&engine);
    
    
    OpenGLSetup session("MyCCraft", &theGame, 800, 600, &engine);
    
    engine.setSession(&session);
    engine.setScene(&theGame);
    
    engine.loadfield("nothing yet");
    cout << "Starting Engine" << endl;
	engine.start();
    
	cout << "Starting display" << endl;
    session.setupWindow(&argc, argv);
	cout << "ending" << endl;
    
    
    
    return 0;
}

