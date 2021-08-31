#include <iostream>
#include <chrono>
#include <string>
#include <exception>
#include <algorithm>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <iostream>
#include <string>
#include <chrono>

class RenderWindow {
private:
	inline static const int width = 800;
	inline static const int height = 800;
	inline static const std::string title = "Rise";
public:
	inline static SDL_Window* window = NULL;
	inline static SDL_Renderer* renderer = NULL;

	inline static bool Start()
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			std::cout << "Failed to start SDL!!!" << std::endl;
			return false;
		}
		if (SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_SHOWN, &window, &renderer) < 0)
	{
			std::cout << SDL_GetError() << std::endl;
			return false;
		}
		SDL_SetWindowTitle(window, title.c_str());
		return true;
	}
	inline static void Close() {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}
};

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

		_nextFrame = std::chrono::steady_clock::now();

		return;
	}

	inline static void Close()
	{
		SDL_DestroyRenderer(_renderer);
		SDL_DestroyWindow(_window);
		SDL_Quit();
		return;
	}

bool update()
	{
	//get next frame time

			case SDL_MOUSEBUTTONUP:
				//Mouse::_released[e.button.button - 1] = true;
				break;

			case SDL_MOUSEWHEEL:
				//Mouse::_scroll = e.wheel.y;

			default:
				break;
			}

			if (e.type == SDL_KEYUP)
			{
				if (e.key.keysym.sym == SDLK_ESCAPE)
				{
					return false;
				}
			}
			else if (e.type == SDL_QUIT) {
				return false;
			}
		}


		Draw();
		SDL_Delay(static_cast<Uint32>((_nextFrame - std::chrono::steady_clock::now()).count() / 1000000));
		return true;
	}

int main(int argc, char* args[])
	{
	RenderWindow::Start();
	SDL_Delay(2000);
	RenderWindow::Close();

	std::cout << "hello" << std::endl;
	return 0;
}