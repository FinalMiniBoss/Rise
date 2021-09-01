#pragma once
#include "Drawable.h"
#include "Platform.h"
#include "Player.h"
#include "Water.h"

class Scene : public Drawable {
public:
	enum class State
	{
		Start,
		Play,
		Pause,
		GameOver,
		Restart
	} state = State::Start;

	Player* player = nullptr;
	Water* water = nullptr;
	std::queue<Platform*> platforms = {};

	Scene();
	~Scene();
};
