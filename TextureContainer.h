#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>

class TextureContainer {
public:
	//Default Constructor, image file path needed to create the texture
    TextureContainer() = default;
    explicit TextureContainer(const std::string& imgPath);

	virtual ~TextureContainer();

    void loadFromFile(const std::string &imgPath);

    virtual void render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip);

	//Get texture data
    SDL_Rect* getRect();
    SDL_Texture* getTexture();

    [[nodiscard]] int getPosX();
    [[nodiscard]] int getPosY();
    [[nodiscard]] int getWidth();
    [[nodiscard]] int getHeight();

protected:

    //The texture
    SDL_Texture* thisTexture{};
	//Having a pre-made rect for the texture may be helpful when using the texture
	SDL_Rect textureRectangle{};
    //Render is used in render()
    SDL_Renderer* textureRenderer{};
    //direct variables of the texture, are initialized then passed to the rect
	int PosX{};
	int PosY{};
	int width{};
	int height{};
};