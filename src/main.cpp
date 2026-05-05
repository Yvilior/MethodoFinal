#include "entity.h"
#include "game.h"
#include <SDL3/SDL.h>
#include <cstdio>

void DrawText(SDL_Renderer* renderer, TTF_Font* font, const char* text, float x, float y)
{
    SDL_Color color = {255, 255, 255, 255};

    SDL_Surface* surface = TTF_RenderText_Blended(font, text, strlen(text), color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    float w, h;
    SDL_GetTextureSize(texture, &w, &h);

    SDL_FRect dst = {x, y, (float)w, (float)h};

    SDL_RenderTexture(renderer, texture, nullptr, &dst);

    SDL_DestroyTexture(texture);
    SDL_DestroySurface(surface);
}

Sint32 main(int argc, char *argv[])
{
    const auto app = new GameApp();
    bool running = true;

    while (running)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
                running = false;

            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    if (app->windTurn == false)
                    {
                        int mx = event.button.x;
                        int my = event.button.y;

                        int cellSize = 100;
                        int gridSize = 500;

                        if (mx >= 0 && my >= 0 && mx < gridSize && my < gridSize)
                        {
                            int cellX = mx / cellSize;
                            int cellY = my / cellSize;

                            float fx = cellX * cellSize + cellSize / 2;
                            float fy = cellY * cellSize + cellSize / 2;

                            Flower* f = new Flower();
                            f->x = fx;
                            f->y = fy;

                            app->entities.push_back(f);
                        }
                    }

                    app->windTurn = !app->windTurn;

                    if (app->turnsRemaining > 0)
                        app->turnsRemaining--;
                }
            }
        }

        SDL_SetRenderDrawColor(app->Renderer, 12, 12, 44, 255);
        SDL_RenderClear(app->Renderer);

        for (auto* e : app->entities)
            if (auto* d = dynamic_cast<Drawable*>(e))
                d->Draw(app);

        if (app->windTurn == false)
            DrawText(app->Renderer, app->font, "Tour du pissenlit", 600, 10);
        else
            DrawText(app->Renderer, app->font, "Tour du vent", 600, 10);

        char buffer[64];
        sprintf(buffer, "%d tours restants", app->turnsRemaining);
        DrawText(app->Renderer, app->font, buffer, 600, 550);

        DrawText(app->Renderer, app->font, "", 600, 250);

        SDL_RenderPresent(app->Renderer);
    }

    delete app;
    return 0;
}