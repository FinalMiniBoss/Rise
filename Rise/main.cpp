#include "main.h"

int main(int argc, char* args[])
	{
	srand(static_cast<unsigned int>(time(NULL)));
	RenderWindow::Start();
	SDL_SetWindowIcon(RenderWindow::window, IMG_Load("assets/Icon.png"));
	Scene* Game = new Scene;
	RenderWindow::scene = Game;
	while (RenderWindow::Update());
	RenderWindow::Close();
	delete Game;
	return 0;
}