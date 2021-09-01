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
	Thrust->anchorPoint = { 0.f,0.f };
	addChild(Thrust);
}

void Player::onUpdate() {
	angle = 5000.f*xVel;
	Thrust->angle = angle;

	if (dynamic_cast<Scene*>(parent) && dynamic_cast<Scene*>(parent)->state != Scene::State::Play)
	{
		return;
	}

	const auto SPACE = SDL_SCANCODE_SPACE;
	const auto LEFT = SDL_SCANCODE_LEFT;
	const auto RIGHT = SDL_SCANCODE_RIGHT;

	const Uint8* keys = SDL_GetKeyboardState(NULL);
	if (keys[SPACE] && fuel>0)
	{
		yVel -= accel;
		if(state!=State::Flying)std::cout << "Now Flying" << std::endl;
		state = State::Flying;
	}
	if (keys[LEFT] && fuel > 0)
	{
		xVel -= accel / 2;
	}
	if (keys[RIGHT] && fuel > 0)
	{
		xVel += accel / 2;
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
	if (state != State::Grounded && fuel > 0) {
		if (
			keys[SPACE] ||
			keys[LEFT] ||
			keys[RIGHT]
			) {
			Thrust->scale = { std::fmin(1.1f,Thrust->scale.x + 0.2f), std::fmin(1.1f,Thrust->scale.y + 0.2f) };
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
	if (state == State::Falling) {
		for (auto& i : parent->children)
		{
			SDL_Rect intersection = { 0,0,0,0 };
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
	}
	if (state == State::Grounded)
	{
		xVel = 0;
		yVel = 0;
	}
	position.x += xVel;
	position.y += yVel;
	yVel += .00005f;

	Thrust->scale = { std::fmax(0.f,Thrust->scale.x - 0.1f), std::fmax(0.f,Thrust->scale.y - 0.1f) };
}