#ifndef COMPONENT_H
#define COMPONENT_H

class GameApp;

class Component
{
public:
	Component () = default;
	virtual ~Component () = default;
	virtual void Update (GameApp *app);
};

#endif