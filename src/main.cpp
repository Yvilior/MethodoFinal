#include "game.h"

/*
 Boucle principale du jeu (Game Loop)
 Gere :
 - les evenements
 - la mise à jour
 - le rendu
 code original du professeur, modifications apporte par Yvain

*/
int main(int argc, char *argv[])
{
	GameApp app;
	bool running = true;

	while (running)
		{
			SDL_Event event;

			while (SDL_PollEvent(&event))
				{
					if (event.type == SDL_EVENT_QUIT)
						running = false;

					app.HandleEvent(event);
				}

			app.Update();
			app.Render();
		}

	return 0;
}