#include "globals.h"
#include "TextureContainer.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

TextureContainer::TextureContainer(const std::string& imgPath) {
	//creates the texture from the provided image
	thisTexture = IMG_LoadTexture(globalRenderer, imgPath.c_str());
	if (thisTexture == nullptr) {
		std::cerr << "Failed to create texture from: " << imgPath << " SDL_IMG_Error: " << IMG_GetError() << '\n';
	}

	//query the texture for its width and height, and assign them to the TextureContainer's width and height
	SDL_QueryTexture(thisTexture, nullptr, nullptr, &width, &height);
	PosX = 0;
	PosY = 0;

	//give the texture's rect the correct values
	textureRectangle = { PosX, PosY, width, height };
    textureRenderer = globalRenderer;
}

TextureContainer::~TextureContainer() {
	if (thisTexture != nullptr) {
		SDL_DestroyTexture(thisTexture);
		thisTexture = nullptr;
	}
}

void TextureContainer::loadFromFile(const std::string &imgPath) {
    //creates the texture from the provided image
    thisTexture = IMG_LoadTexture(globalRenderer, imgPath.c_str());
    if (thisTexture == nullptr) {
        std::cerr << "Failed to create texture from: " << imgPath << " SDL_IMG_Error: " << IMG_GetError() << '\n';
    }

    //query the texture for its width and height, and assign them to the TextureContainer's width and height
    SDL_QueryTexture(thisTexture, nullptr, nullptr, &width, &height);
    PosX = 0;
    PosY = 0;

    //give the texture's rect the correct values
    textureRectangle = { PosX, PosY, width, height };
    textureRenderer = globalRenderer;
}

void TextureContainer::render(int x, int y, SDL_Rect *clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
    SDL_Rect renderRect = {x, y, static_cast<int>(width * globalWindow.getScaleX()),
                           static_cast<int>(height * globalWindow.getScaleY())};

    if (clip != nullptr) {
        renderRect.w = static_cast<int>(clip->w * globalWindow.getScaleX());
        renderRect.h = static_cast<int>(clip->h * globalWindow.getScaleY());
    }

    SDL_RenderCopyEx(textureRenderer, thisTexture, clip,
                     &renderRect, angle, center, flip);
}

SDL_Rect* TextureContainer::getRect() {
	return &textureRectangle;
}

SDL_Texture* TextureContainer::getTexture() {
    return thisTexture;
}

int TextureContainer::getPosX() {
	return PosX;
}

int TextureContainer::getPosY() {
    return PosY;
}

int TextureContainer::getWidth() {
    return width;
}

int TextureContainer::getHeight() {
    return height;
}