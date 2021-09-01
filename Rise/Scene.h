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
	float speed = 0.0005f;
	Player* player = nullptr;
	std::vector<Water*> water = {};
	int platformTimer = 0;

	Scene();
	~Scene();
	void onUpdate();
};
