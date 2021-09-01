#include "Drawable.h"

SDL_Rect Drawable::globalRect()
{
	SDL_Rect sourcerect;
	if (parent) sourcerect = dynamic_cast<Drawable*>(parent)->globalRect();
	else sourcerect = { 0,0,RenderWindow::width,RenderWindow::height };
	SDL_Rect rect = { 0,0,0,0, };

	rect.x = static_cast<int>(sourcerect.x + ((position.x*sourcerect.w) - (anchorPoint.x * size.x * scale.x)));
	rect.y = static_cast<int>(sourcerect.y + ((position.y*sourcerect.h) - (anchorPoint.y * size.y * scale.y)));
	rect.w = static_cast<int>(size.x * scale.x);
	rect.h = static_cast<int>(size.y * scale.y);


	return rect;
}

Drawable::~Drawable()

{
	SDL_DestroyTexture(texture);
}

void Drawable::Draw()
{
	const SDL_Rect* r = new SDL_Rect(globalRect());
	SDL_RenderCopy(RenderWindow::renderer, texture, NULL, r);
	delete r;
	for (auto& child : children)
	{
		dynamic_cast<Drawable*>(child)->Draw();
	}
}

void Drawable::onUpdate()
{
}
