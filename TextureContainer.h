#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>

class TextureContainer {
public:
	//Default Constructor, renderer and image file path needed to create the texture
	TextureContainer(SDL_Renderer* renderer, const std::string& imgPath);

	~TextureContainer();

    SDL_Texture* thisTexture;

	//Get texture data
    const SDL_Rect * getRect();
	[[nodiscard]] int getPosX();
	[[nodiscard]] int getPosY();
	[[nodiscard]] int getWidth();
	[[nodiscard]] int getHeight();

private:
	//

	//Having a pre-made rect for the texture may be helpful when using the texture
	SDL_Rect textureRectangle{};
	//direct variables of the texture, are initialized then passed to the rect
	int PosX;
	int PosY;
	int width{};
	int height{};
};