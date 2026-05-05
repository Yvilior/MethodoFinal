#include "entity.h"

#include "game.h"
#include <SDL3/SDL.h>

Sint32
main (int argc, char *argv[])
{
	const auto app = new GameApp ();
	bool running = true;

	while (running == true)
		{
			SDL_Event event;
			while (SDL_PollEvent (&event) == true)
				{
					if (event.type == SDL_EVENT_QUIT)
						running = false;
				}

			SDL_SetRenderDrawColor (app->Renderer, 12, 12, 44, 255);
			SDL_RenderClear (app->Renderer);

			for (auto* e : app->entities)
				if (auto* d = dynamic_cast<Drawable*>(e))
					d->Draw(app);

			SDL_RenderPresent (app->Renderer);
		}

	delete app;
	return 0;
}