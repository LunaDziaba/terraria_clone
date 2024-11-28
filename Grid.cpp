#include "Grid.h"

namespace Grid {

    Grid::Grid() {
        columns = globalWindow.getWidth() / cellPixelSize;
        rows = globalWindow.getHeight() / cellPixelSize;
    }

    void Grid::refreshGridSize() {
        columns = globalWindow.getWidth() / cellPixelSize;
        rows = globalWindow.getHeight() / cellPixelSize;
    }


}
