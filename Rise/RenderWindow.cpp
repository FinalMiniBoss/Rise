#include "RenderWindow.h"
#include "Scene.h"
bool RenderWindow::Start()
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
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	if (IMG_Init(IMG_INIT_PNG) != (int)IMG_INIT_PNG) {
		std::cout << "Failed to start IMG!!" << std::endl;
		return false;
	}
	SDL_SetWindowTitle(window, title.c_str());
	return true;
}
void RenderWindow::Close() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
bool RenderWindow::Update()
{
	SDL_Event e;

	if (KeyStates[Key::Space] == KeyState::Pressed) { KeyStates[Key::Space] = KeyState::Held; std::cout << "Space Held" << std::endl; }
	if (KeyStates[Key::Space] == KeyState::Released) { KeyStates[Key::Space] = KeyState::Null; std::cout << "Space Null" << std::endl; }
	if (KeyStates[Key::Left] == KeyState::Pressed) { KeyStates[Key::Left] = KeyState::Held; std::cout << "Left Held" << std::endl; }
	if (KeyStates[Key::Left] == KeyState::Released) { KeyStates[Key::Left] = KeyState::Null; std::cout << "Left Null" << std::endl; }
	if (KeyStates[Key::Right] == KeyState::Pressed) { KeyStates[Key::Right] = KeyState::Held; std::cout << "Right Held" << std::endl; }
	if (KeyStates[Key::Right] == KeyState::Released) { KeyStates[Key::Right] = KeyState::Null; std::cout << "Right Null" << std::endl; }
	if (KeyStates[Key::Esc] == KeyState::Pressed) { KeyStates[Key::Esc] = KeyState::Held; std::cout << "Esc Held" << std::endl; }
	if (KeyStates[Key::Esc] == KeyState::Released) { KeyStates[Key::Esc] = KeyState::Null; std::cout << "Esc Null" << std::endl; }

	const Uint8* keyboardstate = SDL_GetKeyboardState(NULL);
	if (keyboardstate[SDL_SCANCODE_SPACE] == 1 && (KeyStates[Key::Space] == KeyState::Null || KeyStates[Key::Space] == KeyState::Released)) { KeyStates[Key::Space] = KeyState::Pressed; std::cout << "Space Pressed" << std::endl; }
	if (keyboardstate[SDL_SCANCODE_SPACE] == 0 && (KeyStates[Key::Space] == KeyState::Pressed || KeyStates[Key::Space] == KeyState::Held)) { KeyStates[Key::Space] = KeyState::Released; std::cout << "Space Released" << std::endl; }
	if (keyboardstate[SDL_SCANCODE_LEFT] == 1 && (KeyStates[Key::Left] == KeyState::Null || KeyStates[Key::Left] == KeyState::Released)) { KeyStates[Key::Left] = KeyState::Pressed; std::cout << "Left Pressed" << std::endl; }
	if (keyboardstate[SDL_SCANCODE_LEFT] == 0 && (KeyStates[Key::Left] == KeyState::Pressed || KeyStates[Key::Left] == KeyState::Held)) { KeyStates[Key::Left] = KeyState::Released; std::cout << "Left Released" << std::endl; }
	if (keyboardstate[SDL_SCANCODE_RIGHT] == 1 && (KeyStates[Key::Right] == KeyState::Null || KeyStates[Key::Right] == KeyState::Released)) { KeyStates[Key::Right] = KeyState::Pressed; std::cout << "Right Pressed" << std::endl; }
	if (keyboardstate[SDL_SCANCODE_RIGHT] == 0 && (KeyStates[Key::Right] == KeyState::Pressed || KeyStates[Key::Right] == KeyState::Held)) { KeyStates[Key::Right] = KeyState::Released; std::cout << "Right Released" << std::endl; }
	if (keyboardstate[SDL_SCANCODE_ESCAPE] == 1 && (KeyStates[Key::Esc] == KeyState::Null || KeyStates[Key::Esc] == KeyState::Released)) { KeyStates[Key::Esc] = KeyState::Pressed; std::cout << "Esc Pressed" << std::endl; }
	if (keyboardstate[SDL_SCANCODE_ESCAPE] == 0 && (KeyStates[Key::Esc] == KeyState::Pressed || KeyStates[Key::Esc] == KeyState::Held)) { KeyStates[Key::Esc] = KeyState::Released; std::cout << "Esc Released" << std::endl; }

	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_QUIT)return false;
	}

	scene->update();

	nextFrame += std::chrono::microseconds(1000000 / frameRate);
	if (std::chrono::steady_clock::now() > nextFrame)nextFrame = std::chrono::steady_clock::now();
	SDL_Delay(static_cast<Uint32>((nextFrame - std::chrono::steady_clock::now()).count() / 1000000));
	SDL_SetRenderDrawColor(renderer, 0xab, 0xcd, 0xef, 0xff);
	SDL_RenderClear(renderer);
	Draw();
	SDL_RenderPresent(renderer);
	return true;
}
void RenderWindow::Draw() { scene->Draw(); }