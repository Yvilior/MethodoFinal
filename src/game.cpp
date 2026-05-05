#include "game.h"
#include "entity.h"
#include <cstdlib>

GameApp::GameApp()
{
	if (SDL_Init(SDL_INIT_VIDEO) == false)
		abort();

	if (TTF_Init() == false)
		abort();

	Window = SDL_CreateWindow("Yvain Guillon", 800, 600, 0);
	if (Window == nullptr)
		abort();

	Renderer = SDL_CreateRenderer(Window, nullptr);
	if (Renderer == nullptr)
		abort();

	font = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 16);
	if (font == nullptr)
		abort();

	entities.push_back(new GridEntity());
}

GameApp::~GameApp()
{
	for (auto e : entities)
		delete e;

	TTF_CloseFont(font);
	TTF_Quit();

	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(Window);
	SDL_Quit();
}