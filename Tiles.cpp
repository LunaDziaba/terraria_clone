#include "globals.h"
#include "Tiles.h"
#include <rapidxml.hpp>
#include <unordered_map>
#include <fstream>
#include <vector>

namespace Tiling {

    /*Tile::Tile(const std::string &xmlFilePath) {
        //Load Tile data from the XML file using RapidXML
        rapidxml::xml_document<> doc;
        rapidxml::xml_node<>* root_node;

        //Parse the XMl file
        std::ifstream file(xmlFilePath);
        if (!file.is_open()) {
            std::cerr << "Could not open file " << xmlFilePath << std::endl;
        }
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
         for (rapidxml::xml_node<>* tileSprite_node = root_node->first_node("TileSprite"); tileSprite_node;
         tileSprite_node = tileSprite_node->next_sibling("TileSprite")) {
             int index = std::stoi(tileSprite_node->first_node("Index")->value());
             int x = std::stoi(tileSprite_node->first_node("X")->value());
             int y = std::stoi(tileSprite_node->first_node("Y")->value());
             int width = std::stoi(tileSprite_node->first_node("Width")->value());
             int height = std::stoi(tileSprite_node->first_node("Height")->value());

             //Create the SDL_Rect and store it in the tileSet
             tileSet[index] = {x, y, width, height};
         }
        loadFromFile(imgPath);
    }*/

    Tile::Tile(const std::string &xmlFilePath) {
        // Load Tile data from the XML file using RapidXML
        rapidxml::xml_document<> doc;
        rapidxml::xml_node<>* root_node;

        // Parse the XML file
        std::ifstream file(xmlFilePath);
        if (!file.is_open()) {
            std::cerr << "Could not open file: " << xmlFilePath << std::endl;
            return;
        }

        std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        if (buffer.size() <= 1) {
            std::cerr << "Error: XML file is empty or invalid." << std::endl;
            return;
        }

        buffer.push_back('\0'); // Null terminate the buffer

        try {
            doc.parse<0>(&buffer[0]);
        } catch (const rapidxml::parse_error& e) {
            std::cerr << "XML parsing error: " << e.what() << std::endl;
            return;
        }

        // Extract Tile data from the XML document
        root_node = doc.first_node("Tile");
        if (!root_node) {
            std::cerr << "Error: <Tile> node not found in XML." << std::endl;
            return;
        }

        if (!root_node->first_node("ImageFilePath") || !root_node->first_node("IsSolid") ||
            !root_node->first_node("IsLiquid") || !root_node->first_node("IsBreakable") ||
            !root_node->first_node("HasGravity") || !root_node->first_node("MiningLevel") ||
            !root_node->first_node("ToolNeeded")) {
            std::cerr << "Error: Missing expected nodes in <Tile>." << std::endl;
            return;
        }

        imgPath = root_node->first_node("ImageFilePath")->value();
        solid = (std::string(root_node->first_node("IsSolid")->value()) == "true");
        liquid = (std::string(root_node->first_node("IsLiquid")->value()) == "true");
        breakable = (std::string(root_node->first_node("IsBreakable")->value()) == "true");
        gravity = (std::string(root_node->first_node("HasGravity")->value()) == "true");
        miningLevel = std::stoi(root_node->first_node("MiningLevel")->value());
        toolNeeded = std::stoi(root_node->first_node("ToolNeeded")->value());

        // Iterate through the "TileSprite" elements
        for (rapidxml::xml_node<>* tileSprite_node = root_node->first_node("TileSprite");
             tileSprite_node; tileSprite_node = tileSprite_node->next_sibling("TileSprite")) {
            int index = std::stoi(tileSprite_node->first_node("Index")->value());
            int x = std::stoi(tileSprite_node->first_node("X")->value());
            int y = std::stoi(tileSprite_node->first_node("Y")->value());
            int width = std::stoi(tileSprite_node->first_node("Width")->value());
            int height = std::stoi(tileSprite_node->first_node("Height")->value());

            // Create the SDL_Rect and store it in the tileSet
            tileSet[index] = {x, y, width, height};
        }

        // Ensure the image path is valid and try loading the image
        if (!imgPath.empty()) {
            loadFromFile(imgPath);
        }
    }


    void Tile::render(int x, int y, const SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) const {
        SDL_Rect renderRect = {x, y, static_cast<int>(width * globalWindow.getScaleX()),
                               static_cast<int>(height * globalWindow.getScaleY())};

        if (clip != nullptr) {
            renderRect.w = static_cast<int>(clip->w * globalWindow.getScaleX());
            renderRect.h = static_cast<int>(clip->h * globalWindow.getScaleY());
        }

        SDL_RenderCopyEx(textureRenderer, thisTexture, clip,
                         &renderRect, angle, center, flip);
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

    const SDL_Rect *Tile::getTileSet(const int index) const {
        return &tileSet[index];
    }

}





