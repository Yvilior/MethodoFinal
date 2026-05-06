#ifndef STATE_H
#define STATE_H

#include <SDL3/SDL.h>
#include <string>

class GameApp;
// Interface des etats du jeu (State Pattern)
// code avant implementation du state par ia
// application et modifications necessaire pour le state fait pas Yvain (avec explication ia)
class GameState
{
public:
	virtual ~GameState() = default;
	virtual void HandleEvent(GameApp* app, SDL_Event& event) = 0;
	virtual void Update(GameApp* app) = 0;
	virtual void Render(GameApp* app) = 0;
};
class PissenlitState : public GameState
{
public:
	void HandleEvent(GameApp* app, SDL_Event& event) override;
	void Update(GameApp* app) override;
	void Render(GameApp* app) override;
};
class VentState : public GameState
{
public:
	int direction;
	VentState();
	void HandleEvent(GameApp* app, SDL_Event& event) override;
	void Update(GameApp* app) override;
	void Render(GameApp* app) override;
};
class EndState : public GameState
{
	std::string resultMessage;
public:
	EndState(const std::string& message);
	void HandleEvent(GameApp* app, SDL_Event& event) override;
	void Update(GameApp* app) override;
	void Render(GameApp* app) override;
};

#endif