#ifndef INC_420J12_MIDTERM_GAME_H
#define INC_420J12_MIDTERM_GAME_H
#include "SDL3/SDL.h"

class GameApp final
{
public:
	SDL_Window *Window = nullptr;
	SDL_Renderer *Renderer = nullptr;

	GameApp ();
	~GameApp ();
};

#endif