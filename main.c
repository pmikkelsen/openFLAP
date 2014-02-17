#include <stdio.h>
#include <SDL2/SDL.h>

#include "SDL_Error.h"
#include "SDL_Texture.h"
#include "ground_pipes.h"
#include "move_bird.h"

const int SCREEN_WIDTH  = 1000;
const int SCREEN_HEIGHT = 600;
const int BIRD_WIDTH = 57;
const int BIRD_HEIGHT = 40;
const int FPS = 60;
SDL_Renderer *renderer = NULL;
SDL_Texture *bird_wup = NULL;
SDL_Texture *bird_wdown = NULL;
SDL_Texture *background = NULL;
SDL_Texture *ground = NULL;
SDL_Window *window = NULL;
SDL_Texture *pipe = NULL;

int pipes[6][2] = {
		{1000, -500},
		{1200, -500},
		{1400, -500},
		{1600, -500},
		{1800, -500},
		{2000, -500}
	};

int ground_x = 0;

int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		SDL_ErrorExit("SDL_Init error");

	window = SDL_CreateWindow("openFLAP",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN);
	
	if (window == NULL) 
		SDL_ErrorExit("Could not create window");

	
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
		SDL_ErrorExit("Coud not create renderer");
	
	bird_wup = loadTexture("resources/flappy-bird-up.png", renderer);
	bird_wdown = loadTexture("resources/flappy-bird-down.png", renderer);
	background = loadTexture("resources/background-2.png", renderer);
	ground = loadTexture("resources/ground-2.png", renderer);
	pipe = loadTexture("resources/pipes-2.png", renderer);
	
	SDL_RenderClear(renderer);		
	render_background(renderer);
	move_world(renderer);
	renderTexture(bird_wup, renderer, 0, 0);
	SDL_RenderPresent(renderer);

	SDL_Event e;
	int running = 1;
	int x = 150;
	int old_y = 0;
	int new_y = 0;
	SDL_Rect bird;
	bird.w = BIRD_WIDTH;
	bird.h = BIRD_HEIGHT;
	bird.x = x;
	bird.y = new_y;

	while (running == 1) {
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT:
				running = 0;
				break;
			case SDL_KEYDOWN:
				new_y = old_y - 100;
				break;
			}
		}
		if (old_y != new_y) {
			SDL_RenderClear(renderer);
			move_bird_up(old_y, new_y, x, 300,  bird_wdown, bird);
			old_y = new_y;
			bird.y = new_y;
		} else if (bird_collided(bird, 550) == 0){
			SDL_RenderClear(renderer);
			render_background(renderer);
			move_world(renderer);
			renderTextureWH(bird_wup, renderer, x, new_y += 60.0 / FPS*8,
				 BIRD_WIDTH, BIRD_HEIGHT);
			SDL_RenderPresent(renderer);
			SDL_Delay(1000/FPS);
			old_y = new_y;
			bird.y = new_y;
		} else {
			printf("bird is dead..\n");
			exit(EXIT_SUCCESS);
		}
	}


	SDL_DestroyTexture(bird_wdown);
	SDL_DestroyTexture(bird_wup);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
