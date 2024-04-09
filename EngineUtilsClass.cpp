#include "EngineUtilsClass.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>

namespace EngineUtils {

	WindowClass::WindowClass() {
		windowName = "";
		thisWindow = nullptr;
		windowWidth = 0;
		windowHeight = 0;
		mouseFocus = false;
		keyboardFocus = false;
		isFullscreen = false;
		isMinimized = false;
	}
	WindowClass::WindowClass(std::string givenName, int width, int height) {
		//Set the window name as the name argument; set all variables to default values
		WindowClass::windowName = givenName;
		thisWindow = nullptr;
		WindowClass::windowWidth = width;
		WindowClass::windowHeight = height;
		mouseFocus = false;
		keyboardFocus = false;
		isFullscreen = false;
		isMinimized = false;
	}

	WindowClass::~WindowClass() {
		//Destroy the window and clear the pointer
		if (thisWindow != nullptr) {
			SDL_DestroyWindow(thisWindow);
			thisWindow = nullptr;
		}
	}

	bool WindowClass::initialize() {
		bool success = true;

		//Create the SDL_window and assign it to the windowClass object
		thisWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			windowWidth, windowHeight, SDL_WINDOW_RESIZABLE);
		if (thisWindow == nullptr) {
			std::cerr << "Failed to create window! SDL Error: " << SDL_GetError() << '\n';
			success = false;
		}
		return success;
	}

	SDL_Renderer* WindowClass::createRenderer() {

		SDL_Renderer* windowRenderer = SDL_CreateRenderer(thisWindow, -1, SDL_RENDERER_ACCELERATED);
		if (windowRenderer == nullptr) {
			std::cerr << "Failed to create renderer! SDL Error: " << SDL_GetError() << '\n';
		}
		return windowRenderer;
	}

	void WindowClass::handleEvent(SDL_Event& event) {
		switch (event.window.event) {
			//if the user requests to close the window, destroy the window
		case SDL_WINDOWEVENT_CLOSE:
			if (thisWindow != nullptr) {
				SDL_DestroyWindow(thisWindow);
				thisWindow = nullptr;
				break;
			}

			//if window restoration is requested, then restore the original size of the window
		case SDL_WINDOWEVENT_RESTORED:
			if (thisWindow != nullptr) {
				SDL_RestoreWindow(thisWindow);
				break;
			}

			//if a window resize is requested change the height and width values to those of the windowEvent's
		case SDL_WINDOWEVENT_RESIZED:
			windowWidth = event.window.data1;
			windowHeight = event.window.data2;
			break;

			//if mouse enters the window, set mouseFocus to true
		case SDL_WINDOWEVENT_ENTER:
			mouseFocus = true;
			break;

			//if mouse leaves the window set mouseFocus to false
		case SDL_WINDOWEVENT_LEAVE:
			mouseFocus = false;
			break;

			//if window gains keyboard focus set keyboardFocus to true
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			keyboardFocus = true;
			break;

			//if window losses keyboard focus set keyboardFocus to false
		case SDL_WINDOWEVENT_FOCUS_LOST:
			keyboardFocus = false;
			break;

			//if the window is maximized
		case SDL_WINDOWEVENT_MAXIMIZED:
			isFullscreen = true;
			break;

			//if the window is minimized
		case SDL_WINDOWEVENT_MINIMIZED:
			isMinimized = true;
			break;
		}
	}

	int WindowClass::getWidth() const {
		return windowWidth;
	}

	int WindowClass::getHeight() const {
		return windowHeight;
	}

	bool WindowClass::hasMouseFocus() const {
		return mouseFocus;
	}

	bool WindowClass::hasKeyboardFocus() const {
		return keyboardFocus;
	}

	bool WindowClass::getIsMinimized() const {
		return isMinimized;
	}

	bool initialize(WindowClass* window, SDL_Renderer*& renderer) {
		//Initialize SDL subsystems
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
			std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << '\n';
			return false;
		}
		else {
			// Initialize SDL_image
			int imgFlags = IMG_INIT_PNG; // Adjust this flag according to the image formats you are using
			if (!(IMG_Init(imgFlags) & imgFlags)) {
				// Error handling if SDL_image initialization fails
				std::cerr << "SDL_image could not initialize! SDL_image_Error: " << IMG_GetError() << '\n';
				return false;
			}
			else {
				// Initialize SDL_mixer
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
					// Error handling if SDL_mixer initialization fails
					std::cerr << "SDL_mixer could not initialize! SDL_mixer_Error: " << Mix_GetError() << '\n';
					return false;
				}
				else {
					// Initialize SDL_ttf
					if (TTF_Init() == -1) {
						// Error handling if SDL_ttf initialization fails
						std::cerr << "SDL_ttf could not initialize! SDL_ttf_Error: " << TTF_GetError() << '\n';
						return false;
					}
					else {
						// If the window pointer is not null, Initialize the window
						if (window != nullptr) {
							if (!window->initialize()) {
								std::cerr << "Window failed to initialize!\n";
							}
							else {
								//Create the renderer from the window
								renderer = window->createRenderer();
								if (renderer == nullptr) {
									std::cerr << "Failed to create Renderer!\n";
								}
							}
						}
					}
				}
			}
		}
		// Initialization successful
		return true;
	}

	void cleanupSDL() {
		//Cleanup SDL Subsystems
		TTF_Quit();
		Mix_Quit();
		IMG_Quit();

		//Clean up SDL
		SDL_Quit();
	}
}