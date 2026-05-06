#include "game.h"
#include "entity.h"
#include "state.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <typeinfo>
// code original par Yvain (version reprise du code du professeur), modifications necessaire pour implementer le state pattern par ia
GameApp::GameApp()
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    window = SDL_CreateWindow("Guillon Yvain Exam Final", 800, 600, 0);
    renderer = SDL_CreateRenderer(window, nullptr);
    font = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 18);
    bigFont = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 48);
    std::srand((unsigned int)std::time(nullptr));
    Entity* e = new Entity();
    grid = new GridComponent();
    e->AddComponent(grid);
    entities.push_back(e);
    state = new PissenlitState();
}
GameApp::~GameApp()
{
    delete state;
    for (auto e : entities) delete e;
    TTF_CloseFont(font);
    TTF_CloseFont(bigFont);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}
void GameApp::HandleEvent(SDL_Event& event)
{
    state->HandleEvent(this, event);
}
void GameApp::Update()
{
    state->Update(this);
}
void GameApp::Render()
{
    SDL_SetRenderDrawColor(renderer, 12, 12, 44, 255);
    SDL_RenderClear(renderer);
    bool isEnd = (dynamic_cast<EndState*>(state) != nullptr);
    if (!isEnd)
    {
        for (auto e : entities)
            e->Render(this);
        char buffer[64];
        sprintf(buffer, "%d tours restants", turnsRemaining);
        SDL_Surface* s = TTF_RenderText_Blended(font, buffer, strlen(buffer), {200, 200, 200, 255});
        SDL_Texture* t = SDL_CreateTextureFromSurface(renderer, s);
        float w, h;
        SDL_GetTextureSize(t, &w, &h);
        SDL_FRect dst = {600, 550, w, h};
        SDL_RenderTexture(renderer, t, nullptr, &dst);
        SDL_DestroyTexture(t);
        SDL_DestroySurface(s);
    }
    state->Render(this);
    SDL_RenderPresent(renderer);
}
void GameApp::ChangeState(GameState* newState)
{
    delete state;
    state = newState;
}
//logique mathematique fait sur papier puis demande a l'ia de mettre en code
void GameApp::ApplyWind(int dir)
{
    int dx[8] = {0,1,0,-1,1,-1,1,-1};
    int dy[8] = {-1,0,1,0,-1,-1,1,1};
    int temp[5][5];
    for(int y=0; y<5; y++) for(int x=0; x<5; x++) temp[y][x] = 0;
    for(int y=0; y<5; y++)
    {
        for(int x=0; x<5; x++)
        {
            if(grid->grid[y][x] == 1)
            {
                int nx = x + dx[dir];
                int ny = y + dy[dir];
                while(nx >= 0 && ny >= 0 && nx < 5 && ny < 5)
                {
                    if(grid->grid[ny][nx] == 0)
                        temp[ny][nx] = 2;
                    nx += dx[dir];
                    ny += dy[dir];
                }
            }
        }
    }
    for(int y=0; y<5; y++)
        for(int x=0; x<5; x++)
            if(temp[y][x] == 2)
                grid->grid[y][x] = 2;
}