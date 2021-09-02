#pragma once

#include <cstdlib>
#include "Drawable.h"
#include "Platform.h"
#include "Player.h"
#include "Water.h"
#include "FuelGuage.h"
#include "PowerUps.h"
class Scene : public Drawable {
public:
	enum class State
	{
		Title,
		Play,
		Pause,
		GameOver,
		Restart
	} state = State::Title;

	Drawable* Title = nullptr;
	Drawable* Tutorial = nullptr;
	int ticker = 0;
	float speed = 0.0005f;
	Player* player = nullptr;
	FuelGuage* fuelGuage = nullptr;
	std::vector<Water*> water = {};
	int platformTimer = 0;
	int platformCounter = 1;

	float powerUpFrequency = 10.f;
	void setup();

	Scene();
	~Scene();
	void onUpdate();
};
