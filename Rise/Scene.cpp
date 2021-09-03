#include "Scene.h"

Scene::Scene()
{
	Water::WaterTexture = SDL_CreateTextureFromSurface(RenderWindow::renderer, IMG_Load("assets/Wave.png"));
	Platform::PlatformTexture = SDL_CreateTextureFromSurface(RenderWindow::renderer, IMG_Load("assets/Platform.png"));
	Platform::BigPlatformTexture = SDL_CreateTextureFromSurface(RenderWindow::renderer, IMG_Load("assets/BigPlatform.png"));
	PowerUp::SpeedTexture = SDL_CreateTextureFromSurface(RenderWindow::renderer, IMG_Load("assets/SpeedPowerUp.png"));
	PowerUp::FuelTexture = SDL_CreateTextureFromSurface(RenderWindow::renderer, IMG_Load("assets/FuelPowerUp.png"));
	PowerUp::InstantFuelTexture = SDL_CreateTextureFromSurface(RenderWindow::renderer, IMG_Load("assets/InstantFuelPowerUp.png"));
	PowerUp::RefuelTexture = SDL_CreateTextureFromSurface(RenderWindow::renderer, IMG_Load("assets/RefuelPowerUp.png"));
	PowerUp::ThrustTexture = SDL_CreateTextureFromSurface(RenderWindow::renderer, IMG_Load("assets/ThrustPowerUp.png"));

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

	GameOver = new Drawable;
	GameOver->texture = SDL_CreateTextureFromSurface(RenderWindow::renderer, IMG_Load("assets/GameOver.png"));
	GameOver->size = { 800,800 };
	GameOver->anchorPoint = { 0.5f,0.5f };
	GameOver->position = { 0.5f,0.5f };
	GameOver->alpha = 0.f;

	Restart = new Drawable;
	Restart->texture = SDL_CreateTextureFromSurface(RenderWindow::renderer, IMG_Load("assets/Restart.png"));
	Restart->size = { 800,800 };
	Restart->anchorPoint = { 0.5f,0.5f };
	Restart->position = { 0.5f,0.5f };
	Restart->alpha = 0.f;

	Pause = new Drawable;
	Pause->texture = SDL_CreateTextureFromSurface(RenderWindow::renderer, IMG_Load("assets/Pause.png"));
	Pause->size = { 800,800 };
	Pause->anchorPoint = { 0.5f,0.5f };
	Pause->position = { 0.5f,0.5f };
	Pause->alpha = 0.f;

	Powerups = new Drawable;
	Powerups->texture = SDL_CreateTextureFromSurface(RenderWindow::renderer, IMG_Load("assets/Powerups.png"));
	Powerups->size = { 800,800 };
	Powerups->anchorPoint = { 0.5f,0.5f };
	Powerups->position = { 0.5f,0.5f };
	Powerups->alpha = 0.f;

	addChild(Tutorial);
	addChild(Restart);
	addChild(Title);
	addChild(GameOver);

	addChild(Pause);
	addChild(Powerups);

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
	addChild(player->Thrust);
	Sparks = new Drawable;
	Sparks->texture = SDL_CreateTextureFromSurface(RenderWindow::renderer, IMG_Load("assets/Sparks.png"));
	Sparks->size = { 100,100 };
	Sparks->anchorPoint = { 0.5f,0.5f };
	Sparks->position = { 0.5f,0.5f };
	Sparks->alpha = 0.f;
	addChild(Sparks);

	Platform* p1 = new Platform;
	p1->size = { 800.f,10.f };
	p1->texture = Platform::BigPlatformTexture;
	p1->position = { 0.5f,0.25f };
	addChild(p1);

	Platform* p2 = new Platform;
	p2->position = { 0.75f,0.1f };
	addChild(p2);
}

void Scene::setup() {
	for (auto& i : children)
	{
		if (dynamic_cast<Platform*>(i) || dynamic_cast<PowerUp*>(i)) {
			dynamic_cast<Drawable*>(i)->position.y = 2.f;
		}
	}

	ticker = 0;
	speed = 0.0005f;
	platformCounter = 1;
	platformTimer = 0;

	powerUpFrequency = 10.f;

	score = 0.f;

	if (state == State::GameOver) state = State::Restart;
	Platform* p1 = new Platform;
	p1->size = { 800.f,10.f };
	p1->texture = Platform::BigPlatformTexture;
	p1->position = { 0.5f,0.25f };
	addChild(p1);

	Platform* p2 = new Platform;
	p2->position = { 0.75f,0.1f };
	addChild(p2);

	player->setup();

	GameOver->alpha = 0.f;
}

Scene::~Scene()
{
}

void Scene::onUpdate() {

	//Position Thrust and sparks textures

	if (state == State::Pause) {
		Pause->alpha = std::min(1.f, Pause->alpha + 0.0333f);
	} else if (state == State::Play) {
		Pause->alpha = std::max(0.f, Pause->alpha - 0.0333f);
	}

	if (state == State::Play)score += 1.f / 60.f;

	Powerups->alpha = Pause->alpha;

	player->Thrust->position = player->position;
	Sparks->position = player->position;
	Sparks->alpha = 0.f;
	if (player->state == Player::State::Dead) Sparks->alpha = 1.f;
	if (ticker%10 == 0)
	{
		Sparks->angle = static_cast<float>(rand() % 360);
		Sparks->scale.x = (static_cast<float>(rand() % 51) / 100.f) + 0.75f;
		Sparks->scale.y = Sparks->scale.x;
	}

	//Move the title around

	ticker++;
	Title->position.x += 0.00008f * std::cosf(ticker/2.f * .01f);
	Title->position.y -= 0.00025f * std::sinf(ticker/2.f * 0.03f);
	GameOver->position = Title->position;
	Pause->position = Title->position;
	// Cache keyboard state

	const Uint8* keys = SDL_GetKeyboardState(NULL);

	// start the Game if Space pressed on Title or Restart

	if ((state == State::Title || state == State::Restart) && RenderWindow::KeyStates[RenderWindow::Key::Space]==RenderWindow::KeyState::Pressed) state = State::Play;

	// Fade title on start

	if (Title->alpha > 0 && state != State::Title) {
		Title->alpha = std::max(0.f, Title->alpha - 0.0167f);
		Tutorial->alpha = Title->alpha;
	}

	//Restart on GameOver and Space

	if (state == State::GameOver && RenderWindow::KeyStates[RenderWindow::Key::Space] == RenderWindow::KeyState::Pressed) {
		setup();

	}

	// Toggle Pause on Esc
	if (state == State::Pause && keys[SDL_SCANCODE_SPACE]) state = State::Play;

	if (RenderWindow::KeyStates[RenderWindow::Key::Esc]==RenderWindow::KeyState::Pressed) {
		if (state == State::Play) state = State::Pause;
		else if (state == State::Pause) state = State::Play;
	}

	//Main Game Loop

	if (state == State::Play || state == State::GameOver)
	{

		//increase falling speeed

		speed += 0.0000003f;

		//spawn new platforms

		platformTimer -= 1;
		if (platformTimer <= 0) {
			platformTimer = 90;
			Platform* p = new Platform;

			//checkpoint platform

			if (platformCounter++ % 25 ==0) {
				p->size = { 800,10 };
				p->texture = Platform::BigPlatformTexture;
				p->position.x = 0.5f;
			}
			else {

				//powerup platform

				if (rand() % (int)powerUpFrequency == 0) {
					PowerUp* powerup = new PowerUp;
					powerUpFrequency += 0.5f;
					powerup->position = p->position;
					addChild(powerup);
				}
			}
			addChild(p);
		}

		//remove entities below the screen

		for (size_t i = 0; i < children.size(); i++)
		{
			if (dynamic_cast<Platform*>(children[i]) || dynamic_cast<PowerUp*>(children[i])) {
				if (dynamic_cast<Drawable*>(children[i])->globalRect().y > RenderWindow::height) {
					Entity* c = children[i];
					removeChild(children[i]);
					delete c;
				}
			}
		}

	}

	//drop platforms, powerups, and player by speed

	if(state == State::Play || state == State::GameOver)
		for (auto c : children)
		{
			if (dynamic_cast<Platform*>(c) || dynamic_cast<Player*>(c) || dynamic_cast<PowerUp*>(c))
			{
				dynamic_cast<Drawable*>(c)->position.y += speed;
			}
		}

	//check for death

	if (player->position.y >= 725.f / 800.f) {
		state = State::GameOver;
		player->state = Player::State::Dead;
		GameOver->alpha = std::fminf(GameOver->alpha + 0.0333f, 1.f);
	}
	Restart->alpha = GameOver->alpha;
	//water animation

	for (size_t i = 0; i < children.size(); i++)
	{

			if (dynamic_cast<Water*>(children[i])) {
				if (dynamic_cast<Water*>(children[i])->globalRect().x > RenderWindow::width) {
					dynamic_cast<Water*>(children[i])->position.x -= 9.f/8.f;
				}
			}
	}


}