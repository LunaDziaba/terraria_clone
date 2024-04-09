#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>

class TextureContainer {
public:
	//Default Constructor, renderer and image file path needed to create the texture
	TextureContainer(SDL_Renderer* renderer, std::string imgPath);

	~TextureContainer();

	//Get texture data
	SDL_Rect getRect();
	int getPosX();
	int getPosY();
	int getWidth();
	int getHeight();

private:
	//
	SDL_Texture* thisTexture;
	//Having a premade rect for the texture may be helpful when using the texture
	SDL_Rect textureRectangle;
	//direct variables of the texture, are initialized then passed to the rect
	int PosX;
	int PosY;
	int width;
	int height;
};