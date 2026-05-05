#include "entity.h"

Entity::~Entity() = default;
Flower::Flower() = default;
Seed::Seed() = default;

void Entity::Update(GameApp *app) {}

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

GridEntity::GridEntity()
{
	for (int y = 0; y < 5; y++)
		for (int x = 0; x < 5; x++)
			grid[y][x] = 0;
}

void Flower::Draw(GameApp* app)
{
	SDL_SetRenderDrawColor(app->Renderer, 34, 85, 34, 255);
	DrawCircle(app->Renderer, (int)x, (int)y, (int)radius);
}

void Seed::Draw(GameApp* app)
{
	SDL_SetRenderDrawColor(app->Renderer, 0, 100, 0, 255);
	DrawCircle(app->Renderer, (int)x, (int)y, (int)radius);
}

void GridEntity::Draw(GameApp* app)
{
	int cellSize = 100;

	SDL_SetRenderDrawColor(app->Renderer, 255, 255, 255, 255);

	for (int y = 0; y < 5; y++)
		{
			for (int x = 0; x < 5; x++)
				{
					SDL_FRect rect = {
						x * (float)cellSize,
						y * (float)cellSize,
						(float)cellSize,
						(float)cellSize
					};
					SDL_RenderRect(app->Renderer, &rect);
				}
		}
}