#ifndef ENTITY_H
#define ENTITY_H
#include <vector>
#include "component.h"
//par yvain
class GameApp;
class Entity
{
public:
	std::vector<Component*> components;
	~Entity();
	void Update(GameApp* app);
	void Render(GameApp* app);
	void AddComponent(Component* c);
};
class GridComponent : public Component
{
public:
	int grid[5][5];
	GridComponent();
	void Render(GameApp* app) override;
};
#endif