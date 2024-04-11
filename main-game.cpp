#include "EngineUtilsClass.h"
#include "TextureContainer.h"
#include "Tiles.h"
#include <SDL.h>
#include <filesystem>
#include <vector>

EngineUtils::WindowClass globalWindow("TerrariaClone", 1280, 720);
EngineUtils::WindowClass* globalWindowPtr = &globalWindow;
SDL_Renderer* globalRenderer;

int SDL_main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    if (!EngineUtils::initialize(globalWindowPtr, globalRenderer)) {
        return 1;
    } else {
        TextureContainer splash_9_0("../Images/Splash_9_0.png");

        Tiling::Tiles dirt_tiles("../xml/dirt_tiles.xml");
        std::vector<std::vector<int>> tileMap = {
                {0, 1, 2},
                {7, 8, 9},
                {12, 13, 14}
        };

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
            int offsetX = dirt_tiles.tileSet[0].w * globalWindow.getScaleX();
            int offsetY = dirt_tiles.tileSet[0].h * globalWindow.getScaleY();
            int middleOfScreenX = globalWindow.getWidth() / 2;
            int middleOfScreenY = globalWindow.getHeight() / 2;
            //Clear the screen
            SDL_SetRenderDrawColor(globalRenderer, 0, 0, 0, 255);
            SDL_RenderClear(globalRenderer);

            splash_9_0.render(0, 0, nullptr, 0, nullptr, SDL_FLIP_NONE);

            for (int row = 0; row < tileMap.size(); row++) {
                for (int col = 0; col < tileMap[row].size(); col++) {
                    int tileIndex = tileMap[row][col];
                    if (tileIndex >= 0) {
                        SDL_Rect* tileRect = &dirt_tiles.tileSet[tileIndex];
                        dirt_tiles.render(middleOfScreenX + (offsetX * col),
                                          middleOfScreenY + (offsetY * row),
                                          tileRect,
                                          0.0, nullptr, SDL_FLIP_NONE);
                    }
                }
            }

            SDL_RenderPresent(globalRenderer);
            //End of frame
        }

        //Game loop ended
        EngineUtils::cleanupSDL();
        return 0;
    }
}