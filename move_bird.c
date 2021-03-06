#include <SDL2/SDL.h>
#include "SDL_Texture.h"
#include "ground_pipes.h"
#include "gui.h"
#include <stdio.h>
#include <time.h>

extern const int FPS;
extern SDL_Renderer *renderer;
extern const int BIRD_WIDTH;
extern const int BIRD_HEIGHT;
extern const int PIPE_WIDTH;
extern int pipes[6][2];
extern int angle;
extern uint32_t lastTime;
extern uint32_t currentTime;
extern uint32_t deltaTime;
extern int framesSinceStart;
extern unsigned long delay;
extern struct timespec time_delay;

int collide_pipe(SDL_Rect bird, int pipe_nr)
{
	if (bird.y <= pipes[pipe_nr][1] + 600) {
		printf("hit a pipe\n");
		return 1;
	} else if (bird.y + bird.h >= pipes[pipe_nr][1] + 800) {
		printf("hit a pipe\n");
		return 1;
	} else {
		return 0;
	}
}	

int bird_collided(SDL_Rect bird, int ground)
{
	if (bird.y + bird.h >= ground) {
		printf("hit the ground\n");
		return 1;
	} else if (bird.x + bird.w >= pipes[1][0] && bird.x + bird.w <= pipes[1][0] + PIPE_WIDTH) {
		int ret = collide_pipe(bird, 1);
		return ret;
	} else if (bird.x <= pipes[1][0] + PIPE_WIDTH && bird.x > pipes[1][0]){
		int ret = collide_pipe(bird, 1);
		return ret;
	} else {
		return 0;
	}
	
}


int move_bird_up(int old_y, int new_y, int x, long time, SDL_Texture *bird, SDL_Rect rec)
{
	int frames = FPS * time / 1000;
	int distance = old_y - new_y;
	int px_pr_frame = distance / frames;

	int y;
	for (y = old_y; time > 0; time -= 1000/FPS) {
		y -= px_pr_frame;
		SDL_RenderClear(renderer);
		render_background(renderer);
		move_world(renderer);
		render_gui();
		SDL_Rect bird_rec;
		bird_rec.y = y;
		bird_rec.x = x;
		bird_rec.w = BIRD_WIDTH;
		bird_rec.h = BIRD_HEIGHT;
		SDL_RenderCopyEx(renderer, bird, NULL, &bird_rec, angle, NULL, SDL_FLIP_NONE);
		SDL_RenderPresent(renderer);
		rec.y = y;
	
		
		if (bird_collided(rec, 550) == 1) {
			return 0;
		} else {
			currentTime = SDL_GetTicks();
			deltaTime = currentTime - lastTime;
			time_delay.tv_nsec -= deltaTime * 100000000;
			nanosleep(&time_delay, NULL);
			time_delay.tv_nsec = delay;
		}
		framesSinceStart++;
		lastTime = SDL_GetTicks();
	}
	return 1;
}
