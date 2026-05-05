#include "game.h"
#include <cstdlib>

GameApp::GameApp ()
{
	if (SDL_Init (SDL_INIT_VIDEO) == false)
		abort ();

	Window = SDL_CreateWindow ("App", 800, 600, 0);
	if (Window == nullptr)
		abort ();

	Renderer = SDL_CreateRenderer (Window, nullptr);
	if (Renderer == nullptr)
		abort ();
}

GameApp::~GameApp ()
{
	SDL_DestroyRenderer (Renderer);
	SDL_DestroyWindow (Window);
	SDL_Quit ();
}