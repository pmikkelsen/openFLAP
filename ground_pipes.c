#include <SDL2/SDL.h>
#include "SDL_Texture.h"

extern const int FPS;
extern SDL_Texture *ground;
extern int ground_x;


void update_ground(SDL_Renderer *renderer)
{
	int w, x;
	int px_pr_frame;
	
	px_pr_frame = 60 / FPS * 2;

	SDL_QueryTexture(ground, NULL, NULL, &w, NULL);
	for (x = ground_x; x <= 1000; x += w) {
		renderTexture(ground, renderer, x, 550);
	}

	if (ground_x > w)
		ground_x = 0;
	else
		ground_x -= px_pr_frame;; 
}

void move_pipes(SDL_Texture *pipe, SDL_Renderer *renderer);
