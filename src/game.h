#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <vector>
// par Yvain ou ia: "ajoute 'xxx' a ton script game'h"
class Entity;
class GridComponent;
class GameState;
class GameApp
{
public:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	TTF_Font* font = nullptr;
	TTF_Font* bigFont = nullptr;
	std::vector<Entity*> entities;
	GridComponent* grid = nullptr;
	GameState* state = nullptr;
	int turnsRemaining = 7;
	GameApp();
	~GameApp();
	void HandleEvent(SDL_Event& event);
	void Update();
	void Render();
	void ChangeState(GameState* newState);
	void ApplyWind(int dir);
};

#endif