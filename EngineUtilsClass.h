#pragma once
#include <SDL.h>
#include <string>

namespace EngineUtils {

	class WindowClass {
	public:
		//Constructor
		WindowClass(std::string givenName, int width, int height);

		//Destructor
		~WindowClass();

		//Create the window
		bool initialize();

		//Create a renderer from the window
		SDL_Renderer* createRenderer();

		//Handle window events
		void handleEvent(const SDL_Event& event);

		//Window dimensions
		[[nodiscard]] int getWidth() const;
		[[nodiscard]] int getHeight() const;
        [[nodiscard]] double getScaleX() const;
        [[nodiscard]] double getScaleY() const;

		//Window foci
		[[nodiscard]] bool hasMouseFocus() const;
		[[nodiscard]] bool hasKeyboardFocus() const;
		[[nodiscard]] bool getIsMinimized() const;

	private:
		//Window name
		std::string windowName;

		//Window data
		SDL_Window* thisWindow;

		//Window dimensions
		int windowWidth;
		int windowHeight;
        double scaleX;
        double scaleY;

		//Window focus
		bool mouseFocus;
		bool keyboardFocus;
		bool isFullscreen;
		bool isMinimized;
	};

	bool initialize(WindowClass* window, SDL_Renderer*& renderer);

	void cleanupSDL();
}