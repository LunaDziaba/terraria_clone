#pragma once
#include <SDL.h>
#include <string>

namespace EngineUtils {

	class WindowClass {
	public:
		//Constructor
		WindowClass();
		WindowClass(std::string givenName, int width, int height);

		//Destructor
		~WindowClass();

		//Create the window
		bool initialize();

		//Create a renderer from the window
		SDL_Renderer* createRenderer();

		//Handle window events
		void handleEvent(SDL_Event& event);

		//Window dimensions
		int getWidth() const;

		int getHeight() const;

		//Window foci
		bool hasMouseFocus() const;

		bool hasKeyboardFocus() const;

		bool getIsMinimized() const;

	private:
		//Window name
		std::string windowName;

		//Window data
		SDL_Window* thisWindow;

		//Window dimensions
		int windowWidth;
		int windowHeight;

		//Window focus
		bool mouseFocus;
		bool keyboardFocus;
		bool isFullscreen;
		bool isMinimized;
	};

	bool initialize(WindowClass* window, SDL_Renderer*& renderer);

	void cleanupSDL();
}