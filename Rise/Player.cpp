#include "Player.h"
#include "Platform.h"
#include "Scene.h"
Player::Player() {
	texture = SDL_CreateTextureFromSurface(RenderWindow::renderer, IMG_Load("assets/Player.png"));
	size = { 100,100 };
	clip = { 0,0,100,100 };
	position = { 0.5f,0.2f };
	anchorPoint = { 0.5f,0.5f };

	Thrust = new Drawable;
	Thrust->texture = SDL_CreateTextureFromSurface(RenderWindow::renderer, IMG_Load("assets/Thrust.png"));
	Thrust->size = { 100,100 };
	Thrust->anchorPoint = { 0.5f,0.5f };
}

void Player::setup() {
	xVel = 0.f;
	yVel = 0.f;
	accel = 0.00015f;
	maxFuel = 100.f;
	fuel = 100.f;
	fuelRate = 1.f;
	refuelRate = 0.5f;
	state = State::Grounded;

	position = { 0.5f,0.25f };

}

void Player::onUpdate() {
	if (state != State::Dead) angle = 5000.f * xVel;
	else { 
		if (xVel >= 0)angle += 0.75f;
		else angle -= 0.75f;
	}
	Thrust->angle = angle;

	const Uint8* keys = SDL_GetKeyboardState(NULL);
	if (dynamic_cast<Scene*>(parent)->state == Scene::State::Play || dynamic_cast<Scene*>(parent)->state == Scene::State::GameOver)
	{
		if ( fuel > 0 && state != State::Dead)
		{
			if (keys[SDL_SCANCODE_SPACE])
			{
				yVel -= accel;
				if(state!=State::Flying)std::cout << "Now Flying" << std::endl;
				state = State::Flying;
			}
			if (keys[SDL_SCANCODE_LEFT] && fuel > 0)
			{
				xVel -= accel / 2;
			}
			if (keys[SDL_SCANCODE_RIGHT] && fuel > 0)
			{
				xVel += accel / 2;
			}
		}
		if (globalRect().x < -25) {
			position.x = 25.f / 800.f;
			xVel /= -2.f;
		}
		if (globalRect().x + globalRect().w > 825) {
			position.x = 775.f / 800.f;
			xVel /= -2.f;
		}
		if (globalRect().y < 0) {
			position.y = 50.f / 800.f;
			yVel = 0;
		}
		if (state != State::Grounded && fuel > 0 && state != State::Dead) {
			if (
				keys[SDL_SCANCODE_SPACE] ||
				keys[SDL_SCANCODE_LEFT] ||
				keys[SDL_SCANCODE_RIGHT]
				) {
				Thrust->scale = { std::fmin(accel/0.00015f,Thrust->scale.x + 0.2f), std::fmin(accel / 0.00015f,Thrust->scale.y + 0.2f) };
				fuel -= fuelRate;
			}
		}
		if (state == State::Grounded) {
			fuel += refuelRate;
		}
		fuel = std::min(std::max(fuel, 0.f),maxFuel);
		if (state == State::Flying && yVel > 0) {
			state = State::Falling;
			std::cout << "Now Falling" << std::endl;
		}
		for (auto& i : parent->children)
			{
			SDL_Rect intersection = { 0,0,0,0 };
			if (state == State::Falling) {
				if (dynamic_cast<Platform*>(i))
				{
					Platform* platform = dynamic_cast<Platform*>(i);
					const SDL_Rect a = {
						globalRect().x+40,
						globalRect().y+ globalRect().h/2 -2,
						20,
						2};
					const SDL_Rect b = platform->globalRect();
					if (SDL_IntersectRect(&a, &b, &intersection))
					{
						position.y = platform->position.y;
						state = State::Grounded;
						std::cout << "Now Grounded" << std::endl;
					}
				}
			}
			if (dynamic_cast<PowerUp*>(i))
			{
				PowerUp* powerup = dynamic_cast<PowerUp*>(i);
				const SDL_Rect a = {
					globalRect().x + 25,
					globalRect().y,
					50,
					globalRect().h / 2 };
				const SDL_Rect b = powerup->globalRect();
				if (SDL_IntersectRect(&a, &b, &intersection) && powerup->alpha != 0.f)
				{
					switch (powerup->powerup) {
					case PowerUp::Powerup::Fuel:
						maxFuel *= 1.1f;
						std::cout << "   Got Fuel PowerUp " << std::endl;
						break;
					case PowerUp::Powerup::InstantFuel:
						fuel = maxFuel;
						std::cout << "   Got InstantFuel PowerUp " << std::endl;
						break;
					case PowerUp::Powerup::Refuel:
						refuelRate *= 1.1f;
						std::cout << "   Got Refuel PowerUp " << std::endl;
						break;
					case PowerUp::Powerup::Speed:
						dynamic_cast<Scene*>(parent)->speed/=1.5f;
						std::cout << "   Got Speed PowerUp " << std::endl;
						break;
					case PowerUp::Powerup::Thrust:
						accel *= 1.1f;
						std::cout << "   Got Thrust PowerUp " << std::endl;
						break;
					}
					powerup->alpha = 0.f;
				}
			}
		}
	
		if (state == State::Grounded)
		{
			xVel = 0;
			yVel = 0;
		}
		position.x += xVel;
		position.y += yVel;
		yVel += accel/3.f;
		Thrust->scale = { std::fmax(0.f,Thrust->scale.x - 0.1f), std::fmax(0.f,Thrust->scale.y - 0.1f) };
	}
}