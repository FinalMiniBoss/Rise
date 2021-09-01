#pragma once

#include <iostream>
#include <chrono>
#include <string>
#include <exception>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

class Scene;

class RenderWindow {
public:
	inline static const int width = 800;
	inline static const int height = 800;
	inline static const std::string title = "Rise";
	inline static SDL_Window* window = NULL;
	inline static SDL_Renderer* renderer = NULL;
	inline static auto nextFrame = std::chrono::steady_clock::now();
	inline static const int frameRate = 60;
	enum class Key { Space, Left, Right, Esc };
	enum class KeyState { Pressed, Held, Released, Null };
	inline static std::map<Key, KeyState> KeyStates = { {Key::Space,KeyState::Null},{Key::Left,KeyState::Null},{Key::Right,KeyState::Null},{Key::Esc,KeyState::Null} };
	inline static Scene* scene = NULL;
public:
	static bool Start();
	static void Close();
	static bool Update();
	static void Draw();
};

