#include "state.h"
#include "game.h"
#include "entity.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
//fait par ia
static void DrawText(SDL_Renderer* renderer, TTF_Font* font, const char* text, float x, float y)
{
    if (!text || strlen(text) == 0) return;
    SDL_Surface* s = TTF_RenderText_Blended(font, text, strlen(text), {255,255,255,255});
    SDL_Texture* t = SDL_CreateTextureFromSurface(renderer, s);

    float w,h;
    SDL_GetTextureSize(t,&w,&h);

    SDL_FRect dst = {x,y,w,h};
    SDL_RenderTexture(renderer,t,nullptr,&dst);

    SDL_DestroyTexture(t);
    SDL_DestroySurface(s);
}
// par yvain
void PissenlitState::HandleEvent(GameApp* app, SDL_Event& event)
{
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
    {
        int size = 100;
        int x = (int)(event.button.x / size);
        int y = (int)(event.button.y / size);
        if(x>=0 && x<5 && y>=0 && y<5)
        {
            app->grid->grid[y][x] = 1;
            app->ChangeState(new VentState());
        }
    }
}
//par Yvain
void PissenlitState::Update(GameApp*) {}
//par Yvain
void PissenlitState::Render(GameApp* app)
{
    DrawText(app->renderer, app->font, "Tour du pissenlit: Placez une fleur", 520, 10);
}
//par Yvain
VentState::VentState()
{
    direction = std::rand() % 8;
}
//par Yvain
void VentState::HandleEvent(GameApp* app, SDL_Event& event)
{
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
    {
        app->ApplyWind(direction);
        app->turnsRemaining--;

        if (app->turnsRemaining <= 0)
        {
            //par Yvain
            bool complete = true;
            for(int y=0; y<5; y++) {
                for(int x=0; x<5; x++) {
                    if(app->grid->grid[y][x] == 0) {
                        complete = false;
                        break;
                    }
                }
            }

            if(complete)
                app->ChangeState(new EndState("VICTOIRE DU PISSENLIT"));
            else
                app->ChangeState(new EndState("VICTOIRE DU VENT"));
        }
        else
        {
            app->ChangeState(new PissenlitState());
        }
    }
}
//par Yvain
void VentState::Update(GameApp*) {}
//par Yvain
void VentState::Render(GameApp* app)
{
    DrawText(app->renderer, app->font, "Tour du vent: Cliquez pour souffler", 520, 10);
    const char* dirs[8] = {"Nord","Est","Sud","Ouest","Nord-Est","Nord-Ouest","Sud-Est","Sud-Ouest"};
    char buffer[64];
    sprintf(buffer, "Direction: %s", dirs[direction]);
    DrawText(app->renderer, app->font, buffer, 550, 250);
}
//par ia
EndState::EndState(const std::string& message) : resultMessage(message) {}
//par ia
void EndState::HandleEvent(GameApp*, SDL_Event&) {}
//par ia
void EndState::Update(GameApp*) {}
//par ia
void EndState::Render(GameApp* app)
{
    SDL_Surface* s = TTF_RenderText_Blended(app->bigFont, resultMessage.c_str(), resultMessage.length(), {255,255,255,255});
    SDL_Texture* t = SDL_CreateTextureFromSurface(app->renderer, s);
    float w,h;
    SDL_GetTextureSize(t,&w,&h);
    SDL_FRect dst = {400.0f - w/2.0f, 300.0f - h/2.0f, w, h};
    SDL_RenderTexture(app->renderer, t, nullptr, &dst);
    SDL_DestroyTexture(t);
    SDL_DestroySurface(s);
}