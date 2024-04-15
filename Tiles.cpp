#include "globals.h"
#include "Tiles.h"
#include <rapidxml.hpp>
#include <unordered_map>
#include <fstream>
#include <vector>

namespace Tiling {

    Tile::Tile(const std::string &xmlFilePath) {
        //Load Tile data from the XML file using RapidXML
        rapidxml::xml_document<> doc;
        rapidxml::xml_node<>* root_node;

        //Parse the XMl file
        std::ifstream file(xmlFilePath);
        std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        buffer.push_back('\0'); //Null terminate the buffer
        doc.parse<0>(&buffer[0]);

        //Extract Tile data from the XML document
        root_node = doc.first_node("Tile");
        imgPath = (root_node->first_node("ImageFilePath")->value());
        solid = (root_node->first_node("IsSolid")->value());
        liquid = (root_node->first_node("IsLiquid")->value());
        breakable = (root_node->first_node("IsBreakable")->value());
        gravity = (root_node->first_node("HasGravity")->value());
        miningLevel = (std::stoi(root_node->first_node("MiningLevel")->value()));
        toolNeeded = (std::stoi(root_node->first_node("ToolNeeded")->value()));
        //Iterate through the "TileSprite" elements
        /*for (rapidxml::xml_node<>* tileSprite_node = root_node->first_node("TileSprite"); tileSprite_node;
        tileSprite_node = tileSprite_node->next_sibling("TileSprite")) {
            int index = std::stoi(tileSprite_node->first_node("Index")->value());
            int x = std::stoi(tileSprite_node->first_node("X")->value());
            int y = std::stoi(tileSprite_node->first_node("Y")->value());
            int width = std::stoi(tileSprite_node->first_node("Width")->value());
            int height = std::stoi(tileSprite_node->first_node("Height")->value());

            //Create the SDL_Rect and store it in the tileSet
            tileSet[index] = {x, y, width, height};
        }*/
        loadFromFile(imgPath);
    }

    bool Tile::isSolid() const {
        return solid;
    }

    bool Tile::isLiquid() const {
        return liquid;
    }

    bool Tile::canBreak() const {
        return breakable;
    }

    bool Tile::hasGravity() const {
        return gravity;
    }

    int Tile::getMiningLevel() const {
        return miningLevel;
    }

    int Tile::getNeededTool() const {
        return toolNeeded;
    }
}





