#ifndef ENTITY_MODULE_H
#define ENTITY_MODULE_H

#include "game.h"

class Entity
{
public:
	Entity() = default;
	virtual ~Entity();
	virtual void Update(GameApp *app);
};

class GridEntity : public Entity, public Drawable
{
public:
	int grid[5][5];
	GridEntity();
	void Draw(GameApp* app) override;
};

class Flower : public Entity, public Drawable
{
public:
	float x = 0;
	float y = 0;
	float radius = 30;
	Flower();
	void Draw(GameApp* app) override;
};

class Seed : public Entity, public Drawable
{
public:
	float x = 150;
	float y = 150;
	float radius = 15;
	Seed();
	void Draw(GameApp* app) override;
};

#endif