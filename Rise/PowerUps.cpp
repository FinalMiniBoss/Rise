#include "PowerUps.h"


PowerUp::PowerUp() {
	size = { 37.5,50 };
	anchorPoint = { 0.5f,1.0f };
	switch (rand() % 5) {
	case 0:
		powerup = Powerup::Speed;
		texture = SpeedTexture;
		std::cout << "   Spawned Speed PowerUp" << std::endl;
		break;
	case 1:
		powerup = Powerup::Fuel;
		texture = FuelTexture;
		std::cout << "   Spawned Fuel PowerUp" << std::endl;
		break;
	case 2:
		powerup = Powerup::Refuel;
		texture = RefuelTexture;
		std::cout << "   Spawned Refuel PowerUp" << std::endl;
		break;
	case 3:
		powerup = Powerup::Thrust;
		texture = ThrustTexture;
		std::cout << "   Spawned Thrust PowerUp" << std::endl;
		break;
	case 4:
		powerup = Powerup::InstantFuel;
		texture = InstantFuelTexture;
		std::cout << "   Spawned InstantFuel PowerUp" << std::endl;
	}

	
}