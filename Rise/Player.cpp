#include "Player.h"
Player::Player() {
	texture = SDL_CreateTextureFromSurface(RenderWindow::renderer, IMG_Load("assets/Player.png"));
	size = { 50,50 };
	clip = { 0,0,100,100 };
	position = { 0.5,0.5 };
	anchorPoint = { 0.5,1.f };
}

void Player::onUpdate() {

	const Uint8* keys = SDL_GetKeyboardState(NULL);
	if (keys[SDL_SCANCODE_SPACE])
	{
		yVel -= accel;
	}
	position.x += xVel;
	position.y += yVel;
	yVel += .00005f;
}