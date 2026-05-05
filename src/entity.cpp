#include "entity.h"

Entity::~Entity () = default;

void Entity::Update (GameApp *app)
{
}

GridEntity::GridEntity()
{
	for (int y = 0; y < 5; y++)
		for (int x = 0; x < 5; x++)
			grid[y][x] = 0;
}

void GridEntity::Draw(GameApp* app)
{
	int cellSize = 100;

	SDL_SetRenderDrawColor(app->Renderer, 255, 255, 255, 255);

	for (int y = 0; y < 5; y++)
		{
			for (int x = 0; x < 5; x++)
				{
					SDL_FRect rect;
					rect.x = x * cellSize;
					rect.y = y * cellSize;
					rect.w = cellSize;
					rect.h = cellSize;

					SDL_RenderRect(app->Renderer, &rect);
				}
		}
}