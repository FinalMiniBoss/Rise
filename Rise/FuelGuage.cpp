#include "FuelGuage.h"
#include "Scene.h"
FuelGuage::FuelGuage() {
	texture = SDL_CreateTextureFromSurface(RenderWindow::renderer, IMG_Load("assets/FuelTank.png"));
	size = { 300,100 };
	anchorPoint = { 0.f,0.f };
	position = { 0.f,0.f };

	Fuel = new Drawable;
	Fuel->texture = SDL_CreateTextureFromSurface(RenderWindow::renderer, IMG_Load("assets/Fuel.png"));
	Fuel->size = { 250,100 };
	anchorPoint = { 0.f,0.f };
	position = { 0.f,0.f };

	BackGuage = new Drawable;
	BackGuage->texture = SDL_CreateTextureFromSurface(RenderWindow::renderer, IMG_Load("assets/BackTank.png"));
	BackGuage->size = { 300,100 };

}

FuelGuage::~FuelGuage() {
	
}

void FuelGuage::onUpdate() {
	Player* pp = dynamic_cast<Scene*>(parent)->player;
	Fuel->scale.x = pp->fuel / pp->maxFuel;
	SDL_SetTextureColorMod(
		Fuel->texture,
		static_cast<Uint8>(std::min(255.f, 510.f-(510.f * (pp->fuel / pp->maxFuel)))),
		static_cast<Uint8>(std::min(255.f, 510.f*(pp->fuel/pp->maxFuel))),
		0);
}