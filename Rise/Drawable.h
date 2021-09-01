#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "Entity.h"

class Entity;

//template<class GT>
//GT clamp(&GT x, GT min, GT max) {
//	x = std::min(std::max(x, min), max);
//}

template<class T>
class Point {
public:
	T x;
	T y;
};

class Drawable : public Entity
{
public:
	float alpha = 1.0f;
	inline float globalAlpha() {
		return alpha * (dynamic_cast<Drawable*>(parent) ? dynamic_cast<Drawable*>(parent)->globalAlpha() : 1.f);
	}

	float angle = 0;
	Point<float>* rotationPoint = nullptr;
	bool Flip = false;

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