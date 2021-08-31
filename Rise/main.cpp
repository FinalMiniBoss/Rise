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

struct RenderWindow;
struct Texture;

struct RenderWindow {
private:
	inline static const int width = 800;
	inline static const int height = 800;
	inline static const std::string title = "Rise";
public:
	inline static SDL_Window* window = NULL;
	inline static SDL_Renderer* renderer = NULL;
	inline static auto nextFrame = std::chrono::steady_clock::now();
	inline static const int frameRate = 60;
public:
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
	inline static bool Update()
	{
		nextFrame += std::chrono::microseconds(1000000 / frameRate);
		if (std::chrono::steady_clock::now() > nextFrame)nextFrame = std::chrono::steady_clock::now();
		SDL_Delay(static_cast<Uint32>((nextFrame - std::chrono::steady_clock::now()).count() / 1000000));

		Draw();
		return true;
	}
	inline static void Draw() {}
};
struct Texture {
	SDL_Texture* texture = NULL;
	SDL_Rect clip = { 0,0,0,0 };
	Texture() = default;
	~Texture() { SDL_DestroyTexture(texture); }
};



int main(int argc, char* args[])
	{
	RenderWindow::Start();
	SDL_Delay(2000);
	RenderWindow::Close();

	std::cout << "hello" << std::endl;
	return 0;
}