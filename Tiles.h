#pragma once
#include "TextureContainer.h"
#include <SDL.h>
#include <SDL_image.h>
#include <unordered_map>
#include <iostream>
#include <string>


//tiling holds various things used for tiling (classes, etc.)
namespace Tiling {

    class Tiles : public TextureContainer {
    public:
        explicit Tiles(const std::string &xmlFilePath);

        ~Tiles() = default;

        std::unordered_map<int, SDL_Rect> tileSet;

        bool isSolid() const;
        bool isLiquid() const;
        bool canBreak() const;
        bool hasGravity() const;

        int getMiningLevel() const;
        int getNeededTool() const;

    private:
        std::string imgPath;

        bool solid;
        bool liquid;
        bool breakable;
        bool gravity;

        int miningLevel;
        int toolNeeded; //0 = pickaxe, 1 = axe, 2 = hammer

    };

}

