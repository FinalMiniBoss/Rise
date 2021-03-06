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
	delete rotationPoint;
}

bool sortChildren(Entity* l1, Entity* l2) {
	return l1->UUID > l2->UUID;
}
void Drawable::Draw()
{
	std::sort(children.begin(), children.end(), sortChildren);
	const SDL_Rect* r = new SDL_Rect(globalRect());
	SDL_SetTextureAlphaMod(texture, static_cast<Uint8>(0xff * globalAlpha()));
	const SDL_Point* pp = (rotationPoint ? new SDL_Point({ (globalRect().x) + (int)(globalRect().w * rotationPoint->x), globalRect().y + (int)(globalRect().h * rotationPoint->y) }) : NULL);
	SDL_RenderCopyEx(
		RenderWindow::renderer,
		texture,
		NULL,
		r,
		angle,
		pp,
		Flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
	delete r;
	delete pp;
	for (auto& child : children)
	{
		dynamic_cast<Drawable*>(child)->Draw();
	}
	
}

void Drawable::onUpdate()
{
}
