#ifndef INC_420J12_MIDTERM_GAME_H
#define INC_420J12_MIDTERM_GAME_H
#include "SDL3/SDL.h"
#include <vector>

class Entity;

class Drawable
{
public:
	virtual ~Drawable () = default;
	virtual void Draw (class GameApp *app) {}
};

class GameApp final
{
public:
	SDL_Window *Window = nullptr;
	SDL_Renderer *Renderer = nullptr;
	std::vector<Entity*> entities;

	GameApp ();
	~GameApp ();
};

#endif