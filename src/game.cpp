//
// Created by yvain on 2026-02-24.
//

#include "game.h"

#include "component.h"

#include <SDL3_image/SDL_image.h>
#include <numeric>

GameApp :: GameApp ()
{
	if (SDL_Init (SDL_INIT_VIDEO) == false)
		{
			SDL_LogCritical (1, "SDL failed to initialize! %s", SDL_GetError ());
			abort ();
		}
	Window = SDL_CreateWindow (AppTitle.c_str (), 800, 600, 0);
	if (Window == nullptr)
		{
			SDL_LogCritical (1, "SDL failed to create window! %s", SDL_GetError ());
			abort ();
		}
	Renderer = SDL_CreateRenderer (Window, nullptr);
	if (Renderer == nullptr)
		{
			SDL_LogCritical (1, "SDL failed to create renderer! %s", SDL_GetError ());
			abort ();
		}

	SDL_SetRenderVSync (Renderer, true);

	Runes = IMG_LoadTexture (Renderer, "res/runes.png");
	if (Runes == nullptr)
		{
			SDL_LogWarn (1, "SDL failed to load images! %s", SDL_GetError ());
		}
	SDL_SetTextureScaleMode (Runes, SDL_SCALEMODE_NEAREST);

	SDL_Time time;
	SDL_GetCurrentTime (&time);
	SDL_srand (time);

	entities.push_back(new Rune(this, 0.25f));
	entities.push_back(new Rune(this, 0.50f));
	entities.push_back(new Rune(this, 0.75f));
	entities.push_back(new Button(this));


}

GameApp :: ~GameApp ()
{
	SDL_DestroyRenderer (Renderer);
	SDL_DestroyWindow (Window);
	SDL_Quit ();
}

void
GameApp :: CalculateFPS (const float DeltaTime)
{
	_frame_times.push_back (DeltaTime);
	if (_frame_times.size () > MAX_SAMPLES)
		{
			_frame_times.erase (_frame_times.begin ());
		}
	const float sum = std::accumulate (_frame_times.begin (), _frame_times.end (), 0.0f);
	const float average = sum / static_cast<float> (_frame_times.size ());
	SampleAverageFPS = average > 0 ? 1.0f / average : 0;
}
void
Drawable :: Draw (GameApp *app)
{
	const auto *filter_entity = dynamic_cast<Entity *> (this);
	SDL_FRect dst = { 0 };
	const TransformComponent *transform
		= filter_entity->GetComponentIfExists<TransformComponent> ();
	dst.x = transform->position.x;
	dst.y = transform->position.y;
	dst.w = transform->size.x;
	dst.h = transform->size.y;

	auto [r, g, b, a] = filter_entity->GetComponentIfExists<ColorComponent> ()->color;
	SDL_SetRenderDrawColor (app->Renderer, r, g, b, a);

	SDL_RenderFillRect (app->Renderer, &dst);
}

Rune :: Rune(GameApp* app, float position)
{
	SDL_Point win;
	SDL_GetWindowSize(app->Window, &win.x, &win.y);

	const auto pos = (SDL_FPoint){ static_cast<float> (win.x) * position - 64.f,
									   static_cast<float> (win.y) * .25f - 64.f };
	constexpr auto size = (SDL_FPoint){ 128.f, 128.f };
	constexpr auto color = (SDL_Color){ 255u, 255u, 255u, 255u };

	components.push_back(new TransformComponent(pos, size));
	components.push_back(new ColorComponent(color));
}
Button :: Button(GameApp* app)
{
	SDL_Point win;
	SDL_GetWindowSize(app->Window, &win.x, &win.y);

	const auto pos = (SDL_FPoint){ static_cast<float> (win.x) /2.f - 110.f,
									   static_cast<float> (win.y) * .75f - 20.f };
	constexpr auto size = (SDL_FPoint){ 220.f, 40.f };
	constexpr auto color = (SDL_Color){ 128u, 255u, 128u, 255u };
	components.push_back(new MouseInteractComponent());
	components.push_back(new TransformComponent(pos, size));
	components.push_back(new ColorComponent(color));
}
