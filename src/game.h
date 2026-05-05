//
// Created by yvain on 2026-02-24.
//

#ifndef INC_420J12_MIDTERM_GAME_H
#define INC_420J12_MIDTERM_GAME_H
#include "SDL3/SDL.h"
#include <string>

#include "entity.h"

#include <vector>

static const std::string AppTitle = "Examen - Mi-session - [Guillon Yvain 2331418]";
static constexpr size_t MAX_SAMPLES = 100;

class GameApp final
{
	std::vector<float> _frame_times;

public:
	SDL_FPoint mouse_pos = { 0 };
	SDL_Window *Window = nullptr;
	SDL_Renderer *Renderer = nullptr;
	SDL_Texture *Runes = nullptr;
	std::vector<Entity *> entities = std::vector<Entity *> ();
	float SampleAverageFPS = 0.0f;

	GameApp ();
	~GameApp ();
	void CalculateFPS (float DeltaTime);
};
class Drawable
{
public:
	Drawable () = default;
	virtual ~Drawable () = default;

	virtual void Draw (GameApp *app);
};

class Rune : public Entity, public Drawable
{
public:
	Rune(GameApp* app, float position);
};

class Button : public Entity, public Drawable
{
public:
	Button(GameApp* app);
};

#endif // INC_420J12_MIDTERM_GAME_H
