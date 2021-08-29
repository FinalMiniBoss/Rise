#include <iostream>
#include <chrono>
#include <string>
#include <exception>
#include <algorithm>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

// This is gonna be ugly

class Engine;







class Engine {
private:
	inline static SDL_Window* _window = NULL;
	inline static SDL_Renderer* _renderer = NULL;

	inline static long long _nextFrame = 0;
	inline static uint16_t _framerate = 60;

	inline static int _screenWidth = 640;
	inline static int _screenHeight = 480;

public:
	inline static void Init(std::string __title, int __width = 640, int __height = 480)
	{
		//Start SDL
	//throw error if fail

		if (SDL_Init(SDL_INIT_VIDEO) < 0) throw std::exception(SDL_GetError());

		//Create Window
		// char* title, posX, posY, sizeX, sizeY, SDL_Flags
		//throw error if fail

		_window = SDL_CreateWindow(__title.c_str(),
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			1920 / 2, 1080 / 2, SDL_WINDOW_SHOWN);
		if (_window == NULL) throw std::exception(SDL_GetError());

		//Get window surface (might be useful)


		//create renderer
		//throw error if fail

		_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);// | SDL_RENDERER_PRESENTVSYNC);
		if (_renderer == NULL) throw std::exception(SDL_GetError());

		//set window icon
		if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) throw std::exception(IMG_GetError());

		if (TTF_Init() == -1) throw std::exception(TTF_GetError());

		SDL_SetWindowIcon(_window, IMG_Load("circles.png"));

		SDL_CaptureMouse(SDL_bool(true));

		return;
	}

	inline static void Close()
	{}

	inline static bool Update()
	{}

	inline static void Draw()
	{}


	inline static SDL_Window* Window() { return Engine::_window; }
	inline static SDL_Renderer* Renderer() { return Engine::_renderer; }
	inline static int Width() { return Engine::_screenWidth; }
	inline static int Height() { return Engine::_screenHeight; }
	inline static long long NextFrame() { return Engine::_nextFrame; }
};

int main(int argc, char* argv[]) {

	Engine::Init("Boop");

	std::cout << ";jklhafsd" << std::endl;
	return 0;
}