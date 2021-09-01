#include "Scene.h"

Scene::Scene()
{
	Water::WaterTexture = SDL_CreateTextureFromSurface(RenderWindow::renderer, IMG_Load("assets/Wave.png"));
	Platform::PlatformTexture = SDL_CreateTextureFromSurface(RenderWindow::renderer, IMG_Load("assets/Platform.png"));
	size = { RenderWindow::width,RenderWindow::height };

	state = State::Title;
	Title = new Drawable;
	Title->texture = SDL_CreateTextureFromSurface(RenderWindow::renderer, IMG_Load("assets/Title.png"));
	Title->anchorPoint = { 0.5f,0.5f };
	Title->position = { 0.5f,0.5f };
	Title->size = { 800.f,400.f };

	Tutorial = new Drawable;
	Tutorial->texture = SDL_CreateTextureFromSurface(RenderWindow::renderer, IMG_Load("assets/Tutorial.png"));
	Tutorial->anchorPoint = { 0.5f,0.5f };
	Tutorial->position = { 0.5f,0.5f };
	Tutorial->size = { 800.f,800.f };
	addChild(Tutorial);
	addChild(Title);

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

	fuelGuage = new FuelGuage;
	addChild(fuelGuage);
	addChild(fuelGuage->Fuel);
	addChild(fuelGuage->BackGuage);

	player = new Player;
	addChild(player);

	Platform* p1 = new Platform;
	p1->scale = { 10.f,1.f };
	p1->position = { 0.5f,0.2f };
	addChild(p1);

	Platform* p2 = new Platform;
	p2->position = { 0.75f,0.1f };
	addChild(p2);
}

Scene::~Scene()
{
}

void Scene::onUpdate() {
	ticker++;
	Title->position.x += 0.00025f * std::cosf(ticker/2.f * .01f);
	Title->position.y -= 0.0005f * std::sinf(ticker/2.f * 0.03f);
	const Uint8* keys = SDL_GetKeyboardState(NULL);
	if (state == State::Title && keys[SDL_SCANCODE_SPACE]) state = State::Play;
	if (RenderWindow::KeyStates[RenderWindow::Key::Esc]==RenderWindow::KeyState::Pressed) {
		if (state == State::Play) state = State::Pause;
		else if (state == State::Pause) state = State::Play;
	}
	if (Title->alpha > 0 && state != State::Title) {
		Title->alpha = std::max(0.f, Title->alpha - 0.0167f);
		Tutorial->alpha = Title->alpha;
	}
	if (state == State::Play)
	{
		speed += 0.0000003f;
		platformTimer -= 1;
		if (platformTimer <= 0) {
			platformTimer = 90;
			Platform* p = new Platform;
			if (platformCounter++ % 25 ==0) {
				p->scale = { 10.f,1.f };
				p->position.x = 0.5f;
			}
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
		}

		for (auto c : children)
		{
			if (dynamic_cast<Platform*>(c) || dynamic_cast<Player*>(c))
			{
				dynamic_cast<Drawable*>(c)->position.y += speed;
			}
		}
	}
	for (size_t i = 0; i < children.size(); i++)
	{

			if (dynamic_cast<Water*>(children[i])) {
				if (dynamic_cast<Water*>(children[i])->globalRect().x > RenderWindow::width) {
					dynamic_cast<Water*>(children[i])->position.x -= 9.f/8.f;
				}
			}
	}
}