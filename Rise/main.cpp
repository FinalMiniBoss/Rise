#include "main.h"

int main(int argc, char* args[])
	{

	//test window
	RenderWindow::Start();

	Scene* Game = new Scene;
	RenderWindow::scene = Game;
	while (RenderWindow::Update());
	RenderWindow::Close();
	delete Game;
	return 0;
}