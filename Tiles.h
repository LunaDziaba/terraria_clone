#pragma once
#include "TextureContainer.h"
#include <SDL.h>
#include <SDL_image.h>
#include <unordered_map>
#include <iostream>
#include <string>


//tiling holds various things used for tiling (classes, etc.)
namespace Tiling {

    class Tile : public TextureContainer {
    public:
        Tile() = default;
        explicit Tile(const std::string &xmlFilePath);

        //std::unordered_map<int, SDL_Rect> tileSet;
        void render(int x, int y, const SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) const;

        [[nodiscard]] bool isSolid() const;
        [[nodiscard]] bool isLiquid() const;
        [[nodiscard]] bool canBreak() const;
        [[nodiscard]] bool hasGravity() const;

        [[nodiscard]] int getMiningLevel() const;
        [[nodiscard]] int getNeededTool() const;

        [[nodiscard]] const SDL_Rect *getTileSet(int index) const;

    private:
        std::string imgPath;


        bool solid{};
        bool liquid{};
        bool breakable{};
        bool gravity{};

        int miningLevel{};
        int toolNeeded{}; //0 = pickaxe, 1 = axe, 2 = hammer

        SDL_Rect tileSet[];
    };

}

