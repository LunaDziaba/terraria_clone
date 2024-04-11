#pragma once
#include "EngineUtilsClass.h"
#include <SDL.h>

//Instantiate the window with name TerrariaClone, and initial width and height of 1280x720
extern EngineUtils::WindowClass globalWindow;
//Create a pointer to globalWindow and give it the address of globalWindow
extern EngineUtils::WindowClass* globalWindowPtr;

//Instantiate the global renderer
extern SDL_Renderer* globalRenderer;