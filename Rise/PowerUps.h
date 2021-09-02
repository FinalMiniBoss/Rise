#pragma once
#include "Drawable.h"
class PowerUp :
    public Drawable
{
public:
	inline static SDL_Texture* SpeedTexture = nullptr;
	inline static SDL_Texture* FuelTexture = nullptr;
	inline static SDL_Texture* InstantFuelTexture = nullptr;
	inline static SDL_Texture* RefuelTexture = nullptr;
	inline static SDL_Texture* ThrustTexture = nullptr;
	enum class Powerup
	{
		Speed,
		Fuel,
		InstantFuel,
		Refuel,
		Thrust
	}powerup = Powerup::Speed;
    PowerUp();
};

