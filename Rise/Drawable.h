#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "Entity.h"

class Entity;

template<class T>
class Point {
public:
	T x;
	T y;
};

class Drawable : public Entity
{
public:
	bool visible = true;
	Point<float> position = { 0,0 };
	Point<float> size = { 0,0 };
	Point<float> scale = { 1.f,1.f };
	Point<float> anchorPoint = { 0.f,0.f };

	SDL_Texture* texture = NULL;
	SDL_Rect clip = { 0,0,1,1 };

	SDL_Rect globalRect();

	Drawable() = default;

	~Drawable();

	void Draw();
	virtual void onUpdate();

private:

};