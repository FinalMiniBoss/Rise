#include "Scene.h"

Scene::Scene()
{
	Water::WaterTexture = SDL_CreateTextureFromSurface(RenderWindow::renderer, IMG_Load("assets/Wave.png"));
	Platform::PlatformTexture = SDL_CreateTextureFromSurface(RenderWindow::renderer, IMG_Load("assets/Platform.png"));
	size = { RenderWindow::width,RenderWindow::height };
	for (int i = 0; i <= 8; i++) {
		Water* w = new Water((float)i,1);
		water.push_back(w);
		addChild(w);
	}
	for (int i = 0; i <= 8; i++) {
		Water* w = new Water((float)i,2);
		water.push_back(w);
		w->position.x += 0.03225f;
		addChild(w);
	}
	for (int i = 0; i <= 8; i++) {
		Water* w = new Water((float)i,3);
		water.push_back(w);
		w->position.x += (0.09f);
		addChild(w);
	}
	player = new Player;
	addChild(player);
}

Scene::~Scene()
{
	
}

void Scene::onUpdate() {
	speed += 0.0000003f;
	platformTimer -= 1;
	if (platformTimer <= 0) {
		platformTimer = 90;
		Platform* p = new Platform;
		addChild(p);
	}
	for (size_t i = 0; i < children.size(); i++)
	{
		if (dynamic_cast<Platform*>(children[i])) {
			if (dynamic_cast<Platform*>(children[i])->globalRect().y > RenderWindow::height) {
				Entity* c = children[i];
				removeChild(children[i]);
				delete c;
			}
		}
		if (dynamic_cast<Water*>(children[i])) {
			if (dynamic_cast<Water*>(children[i])->globalRect().x > RenderWindow::width) {
				dynamic_cast<Water*>(children[i])->position.x -= 9.f/8.f;
			}
		}
	}

	for (auto c : children)
	{
		if (dynamic_cast<Platform*>(c) || dynamic_cast<Player*>(c))
		{
			dynamic_cast<Drawable*>(c)->position.y += speed;
		}
	}
}