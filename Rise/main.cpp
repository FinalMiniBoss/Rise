#include "main.h"

int main(int argc, char* args[])
	{

	//test window
	RenderWindow::Start();

	Scene* q = new Scene;
	Drawable* d = new Drawable;
	d->texture = SDL_CreateTextureFromSurface(RenderWindow::renderer, IMG_Load("assets/circles.png"));
	d->position = { .50,.50 };
	d->size = { 100,50 };
	q->addChild(d);
	RenderWindow::scene = q;
	while (RenderWindow::Update());
	RenderWindow::Close();
	delete q;
	return 0;
}