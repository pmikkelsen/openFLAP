#include <SDL2/SDL.h>
#include "SDL_Texture.h"
#include "ground_pipes.h"

extern const int FPS;
extern SDL_Renderer *renderer;

int bird_collided(SDL_Rect bird, int ground)
{
	if (bird.y + bird.h >= ground)
		return 1;
	else 
		return 0;
}


void move_bird_up(int old_y, int new_y, int x, long time, SDL_Texture *bird)
{
	int frames = FPS * time / 1000;
	int distance = old_y - new_y;
	int px_pr_frame = distance / frames;

	int y;
	for (y = old_y; time > 0; time -= 1000/FPS) {
		y -= px_pr_frame;
		SDL_RenderClear(renderer);
		render_background(renderer);
		update_ground(renderer); 	
		renderTexture(bird, renderer, x, y);
		SDL_RenderPresent(renderer);
		SDL_Delay(1000/FPS);
	}
}
