#ifndef COMPONENT_H
#define COMPONENT_H
//par Yvain
class GameApp;
class Component
{
public:
	Component() = default;
	virtual ~Component();
	virtual void Update(GameApp* app);
	virtual void Render(GameApp* app);
};
#endif