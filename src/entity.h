#ifndef ENTITY_MODULE_H
#define ENTITY_MODULE_H

#include "game.h"

class Entity
{
public:
	Entity () = default;
	virtual ~Entity ();
	virtual void Update (GameApp *app);
};

class GridEntity : public Entity, public Drawable
{
public:
	int grid[5][5];

	GridEntity();
	void Draw(GameApp* app) override;
};

#endif