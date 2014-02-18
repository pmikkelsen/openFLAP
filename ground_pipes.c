#include <stdlib.h>
#include <SDL2/SDL.h>
#include "SDL_Texture.h"

extern const int FPS;
extern SDL_Texture *ground;
extern SDL_Texture *pipe;
extern const int PIPE_WIDTH;
extern int ground_x;
extern int pipes[6][2];

void update_pipes(SDL_Renderer *renderer);

int random_height()
{
	int random = rand();
	random = (random  % 450) - 700;
	
	if (random < -550)
		random = -550;
	else if (random > -300)
		random = -300;
	
	return random;
}

void generate_pipes(SDL_Renderer *renderer)
{
	int i;
	for (i = 0; i < 5; i++) {
		pipes[i][0] = pipes[i+1][0];
		pipes[i][1] = pipes[i+1][1];
	}
	pipes[5][0] = 1000;
	pipes[5][1] = random_height();	
	update_pipes(renderer);
}

void update_pipes(SDL_Renderer *renderer)
{
	if (pipes[0][0] <= -200) {
		generate_pipes(renderer);
	} else {
		int px_pr_frame = 60 / FPS * 3;
		int i;
		for (i = 0; i < 6; i++) {
			renderTextureWH(pipe, renderer, pipes[i][0], 
					pipes[i][1], PIPE_WIDTH, 1400);
			pipes[i][0] -= px_pr_frame;
		}
	}	
}


void move_world(SDL_Renderer *renderer)
{
	update_pipes(renderer);
	
	int w, x;
	int px_pr_frame;
	
	px_pr_frame = 60 / FPS * 3;

	SDL_QueryTexture(ground, NULL, NULL, &w, NULL);
	for (x = ground_x; x <= 1000; x += w) {
		renderTexture(ground, renderer, x, 550);
	}

	if (ground_x > w)
		ground_x = 0;
	else
		ground_x -= px_pr_frame;
}

