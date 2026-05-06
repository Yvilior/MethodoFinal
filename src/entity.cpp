#include "entity.h"
#include "game.h"
// par ia
void DrawCircle(SDL_Renderer* renderer, int cx, int cy, int radius)
{
	for (int w = 0; w < radius * 2; w++)
		{
			for (int h = 0; h < radius * 2; h++)
				{
					int dx = radius - w;
					int dy = radius - h;

					if ((dx * dx + dy * dy) <= (radius * radius))
						SDL_RenderPoint(renderer, cx + dx, cy + dy);
				}
		}
}
// par Yvain
Entity::~Entity()
{
	for (auto c : components)
		delete c;
}
//par Yvain
void Entity::Update(GameApp* app)
{
	for (auto c : components)
		c->Update(app);
}
// par Yvain
void Entity::Render(GameApp* app)
{
	for (auto c : components)
		c->Render(app);
}
//par Yvain
void Entity::AddComponent(Component* c)
{
	components.push_back(c);
}
//par ia
GridComponent::GridComponent()
{
	for(int y=0;y<5;y++)
		for(int x=0;x<5;x++)
			grid[y][x]=0;
}
//par ia
void GridComponent::Render(GameApp* app)
{
	int size = 100;
	for(int y=0;y<5;y++)
		{
			for(int x=0;x<5;x++)
				{
					SDL_FRect r = {
						(float)(x*size),
						(float)(y*size),
						(float)size,
						(float)size
					};
					SDL_SetRenderDrawColor(app->renderer,255,255,255,255);
					SDL_RenderRect(app->renderer,&r);
					if(grid[y][x]==1)
						{
							SDL_SetRenderDrawColor(app->renderer,0,255,0,255);
							DrawCircle(app->renderer,
								x*size + size/2,
								y*size + size/2,
								30);
						}
					if(grid[y][x]==2)
						{
							SDL_SetRenderDrawColor(app->renderer,200,200,200,255);
							DrawCircle(app->renderer,
								x*size + size/2,
								y*size + size/2,
								10);
						}
				}
		}
}