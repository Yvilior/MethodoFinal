//
// Created by yvain on 2026-02-24.
//

#include "component.h"
#include <SDL3/SDL_mouse.h>
#include "game.h"

TransformComponent::TransformComponent (const SDL_FPoint &_position, const SDL_FPoint &_size)
	: position (_position), size (_size)
{
}

void
TransformComponent::UpdateComponent (GameApp *app, Entity *entity)
{
}

ColorComponent::ColorComponent (const SDL_Color &_color) : color (_color)
{
	_default_color = color;
}

void
ColorComponent::UpdateComponent (GameApp *app, Entity *entity)
{
	// Si l'entité elle-même a un MouseInteractComponent
	if (const auto *mouse_interact = entity->GetComponentIfExists<MouseInteractComponent>())
		{
			switch (mouse_interact->mouse_state)
				{
				case UNSELECTED:
					color = _default_color;
					break;
				case CLICKED:
					color = (SDL_Color){ 255, 0, 0, 255 };
					break;
				default:
					break;
				}
		}
	else
		{
			// Sinon, on regarde si le bouton a été cliqué
			for (Entity* e : app->entities)
				{
					if (auto* button = dynamic_cast<Button*>(e))
						{
							if (auto* mouse = button->GetComponentIfExists<MouseInteractComponent>())
								{
									if (mouse->mouse_state == CLICKED)
										{
											color = (SDL_Color){
												static_cast<Uint8>(SDL_rand(256)),
												static_cast<Uint8>(SDL_rand(256)),
												static_cast<Uint8>(SDL_rand(256)),
												255
											};
										}
								}
						}
				}
		}
}


void
MouseInteractComponent::UpdateComponent (GameApp *app, Entity *entity)
{
	const auto *transform = entity->GetComponentIfExists<TransformComponent>();
	if (transform == nullptr)
		return;

	// Par défaut, on remet l'état à UNSELECTED
	mouse_state = UNSELECTED;

	// Vérifie si la souris est dans les limites du rectangle
	const bool inside_x = app->mouse_pos.x >= transform->position.x &&
						  app->mouse_pos.x <= transform->position.x + transform->size.x;
	const bool inside_y = app->mouse_pos.y >= transform->position.y &&
						  app->mouse_pos.y <= transform->position.y + transform->size.y;

	if (inside_x && inside_y)
		{
			// Si le bouton gauche est enfoncé, on considère que c'est un clic
			int buttons = SDL_GetMouseState(nullptr, nullptr);
			if ((buttons & SDL_BUTTON_LMASK) != 0)
				{
					mouse_state = CLICKED;
				}
		}
}
