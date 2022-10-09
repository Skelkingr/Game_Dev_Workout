#include "Game.h"

int main(int argc, char** argv)
{
	Game game;

	bool initSuccess = game.Initialize();
	if (initSuccess)
	{
		game.RunLoop();
	}

	game.Shutdown();
	return 0;
}