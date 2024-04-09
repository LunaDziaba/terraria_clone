#include "TextureContainer.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

TextureContainer::TextureContainer(SDL_Renderer* renderer, const std::string& imgPath) {
	//creates the texture from the provided image
	thisTexture = IMG_LoadTexture(renderer, imgPath.c_str());
	if (thisTexture == nullptr) {
		std::cerr << "Failed to create texture from: " << imgPath << " SDL_IMG_Error: " << IMG_GetError() << '\n';
	}

	//query the texture for its width and height, and assign them to the TextureContainer's width and height
	SDL_QueryTexture(thisTexture, nullptr, nullptr, &width, &height);
	PosX = 0;
	PosY = 0;

	//give the texture's rect the correct values
	textureRectangle = { PosX, PosY, width, height };
}

TextureContainer::~TextureContainer() {
	if (thisTexture != nullptr) {
		SDL_DestroyTexture(thisTexture);
		thisTexture = nullptr;
	}
}

const SDL_Rect * TextureContainer::getRect() {
	return &textureRectangle;
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