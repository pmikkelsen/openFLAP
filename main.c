#include <stdio.h>
#include <time.h>
#include <SDL2/SDL.h>

#include "SDL_Error.h"
#include "SDL_Texture.h"
#include "ground_pipes.h"
#include "move_bird.h"
#include "gui.h"

const int SCREEN_WIDTH  = 1000;
const int SCREEN_HEIGHT = 600;
const int BIRD_WIDTH = 64;
const int BIRD_HEIGHT = 45;
const int PIPE_WIDTH = 75;
const int FPS = 60;
int point = 0;
SDL_Renderer *renderer = NULL;
SDL_Texture *bird_wup = NULL;
SDL_Texture *bird_wdown = NULL;
SDL_Texture *background = NULL;
SDL_Texture *ground = NULL;
SDL_Window *window = NULL;
SDL_Texture *pipe = NULL;

int background_i;

int angle = -30;

int pipes[6][2] = {
		{1000, -1400},
		{1200, -300},
		{1400, -360},
		{1600, -420},
		{1800, -480},
		{2000, -550}
	};

int ground_x = 0;

uint32_t lastTime;
uint32_t currentTime;
uint32_t deltaTime;
int framesSinceStart = 0;

unsigned long delay;
struct timespec time_delay;


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
		
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
		SDL_ErrorExit("Coud not create renderer");

	bird_wup = loadTexture("resources/flappy-bird-up.png", renderer);
	bird_wdown = loadTexture("resources/flappy-bird-down.png", renderer);
	background = loadTexture("resources/background.png", renderer);
	ground = loadTexture("resources/ground.png", renderer);
	pipe = loadTexture("resources/pipes.png", renderer);
	
	SDL_RenderClear(renderer);		
	render_background(renderer);
	move_world(renderer);
	renderTexture(bird_wup, renderer, 0, 0);
	SDL_RenderPresent(renderer);

	init_gui();

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
	int distance_fdown = 0;

	lastTime = SDL_GetTicks();
	uint32_t startTime = SDL_GetTicks();
	
	delay = 1000000000/FPS;
	time_delay.tv_sec = 0;
	time_delay.tv_nsec = delay;	

	while (running == 1) {
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT:
				printf("got signal to end\n");
				running = 0;
				break;
			case SDL_KEYDOWN:
				new_y = old_y - 75;
				distance_fdown = 0;
				angle = -30;
				break;
			}
		}
		if (old_y != new_y) {
			SDL_RenderClear(renderer);
			running = move_bird_up(old_y, new_y, x, 200,  bird_wdown, bird);
			old_y = new_y;
			bird.y = new_y;
		} else if (bird_collided(bird, 550) == 0){
			SDL_RenderClear(renderer);
			render_background(renderer);
			move_world(renderer);
			render_gui();
			new_y += (60.0 / FPS) * (distance_fdown * 0.35);
			bird.y = new_y;
			SDL_RenderCopyEx(renderer, bird_wup, NULL, &bird, angle,
				 NULL, SDL_FLIP_NONE);
			SDL_RenderPresent(renderer);
			currentTime = SDL_GetTicks();
			deltaTime = currentTime - lastTime;
			time_delay.tv_nsec -= deltaTime * 1000000;
			nanosleep(&time_delay, NULL);
			time_delay.tv_nsec = delay;
			framesSinceStart++;
			old_y = new_y;
			if (angle < 90 && distance_fdown != 0) {
				angle += 60.0 / FPS *4.5;
				distance_fdown += 60.0 / FPS;
			} else if (angle == -30){
				distance_fdown += 60.0 / FPS;
			}
		} else {
			running = 0;
		}
		lastTime = SDL_GetTicks();
	}

	uint32_t endTime = SDL_GetTicks();
	float seconds = (endTime - startTime) / 1000.0;
	float avg_fps = framesSinceStart / seconds;
	
	printf("score: %d\n", point);
	printf("%d frames in %f seconds\n", framesSinceStart, seconds);
	printf("avg. FPS: %f\n", avg_fps);
	exit(EXIT_SUCCESS);


	SDL_DestroyTexture(bird_wdown);
	SDL_DestroyTexture(bird_wup);
	SDL_DestroyTexture(background);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
