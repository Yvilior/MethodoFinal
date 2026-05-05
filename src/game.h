#ifndef INC_420J12_MIDTERM_GAME_H
#define INC_420J12_MIDTERM_GAME_H

#include "SDL3/SDL.h"
#include <SDL3_ttf/SDL_ttf.h>
#include <vector>

class Entity;

class Drawable
{
public:
	virtual ~Drawable() = default;
	virtual void Draw(class GameApp *app) {}
};

class GameApp final
{
public:
	SDL_Window *Window = nullptr;
	SDL_Renderer *Renderer = nullptr;

	TTF_Font* font = nullptr;

	std::vector<Entity*> entities;

	bool windTurn = false;
	int turnsRemaining = 10;

	GameApp();
	~GameApp();
};

#endif