#pragma once
#include "globals.h"
#include <SDL.h>
#include <vector>


namespace Grid {
    struct gridCell : SDL_Rect {
        gridCell(int x, int y );
    };
    class Grid {
    protected:
        const int cellPixelSize = 16;
        int columns;
        int rows;


    public:

        Grid();

        ~Grid() = default;

        void refreshGridSize();
        void renderGridLines();

        std::vector<int> getCellCoords(int cell);
    };
}