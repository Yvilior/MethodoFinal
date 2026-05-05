#ifndef ENTITY_MODULE_H
#define ENTITY_MODULE_H

class GameApp;

class Entity
{
public:
	Entity () = default;
	virtual ~Entity ();
	virtual void Update (GameApp *app);
};

#endif