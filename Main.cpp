#include "stdafx.h"
#include "Engine.h"


int main()
{
	Engine * engine_ptr;
	engine_ptr = new Engine;

	engine_ptr[0].start();

	delete engine_ptr;

	return 0;



	/*
	// Declare an instance of Engine
	Engine engine;

	// Start the engine
	engine.start();

	// Quit in the usual way when the engine is stopped
	return 0;*/
}