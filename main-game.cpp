#include "EngineUtilsClass.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>


//Instantiate the window with name TerrariaClone, and initial width and height of 1280x720
EngineUtils::WindowClass globalWindow("TerrariaClone", 1280, 720);
//Create a pointer to globalWindow and give it the address of globalWindow
EngineUtils::WindowClass* globalWindowPtr = &globalWindow;

//Instantiate the global renderer
SDL_Renderer* globalRenderer;



int SDL_main(int argc, char* argv[])
{
    if (!EngineUtils::initialize(globalWindowPtr, globalRenderer)) {
        return 1;
    } else {
        //Game loop
        bool quit = false;
        while (!quit) {

            //Event handling
            SDL_Event e;
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                }
                globalWindow.handleEvent(e);
            //End of event handling
            }
            //Clear the screen
            SDL_SetRenderDrawColor(globalRenderer, 0, 0, 0, 255);
            SDL_RenderClear(globalRenderer);

            SDL_Rect rect = {globalWindow.getWidth() / 4, globalWindow.getHeight() / 4, 
                globalWindow.getWidth() / 2, globalWindow.getHeight() / 2};
            SDL_SetRenderDrawColor(globalRenderer, 0, 0, 255, 255); // Blue color
            SDL_RenderFillRect(globalRenderer, &rect);

            SDL_RenderPresent(globalRenderer);
            //End of frame
        }

        //Game loop ended
        EngineUtils::cleanupSDL();
        return 0;
    }
}