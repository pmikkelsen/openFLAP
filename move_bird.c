#include <SDL2/SDL.h>
#include "SDL_Texture.h"
#include "ground_pipes.h"
#include <stdio.h>

extern const int FPS;
extern SDL_Renderer *renderer;
extern const int BIRD_WIDTH;
extern const int BIRD_HEIGHT;
extern int pipes[6][2];

int collide_pipe(SDL_Rect bird, int pipe_nr)
{
	if (bird.y <= pipes[pipe_nr][1] + 600)
		return 1;
	else if (bird.y + bird.h >= pipes[pipe_nr][1] + 800)
		return 1;
	else
		return 0;
}	

int bird_collided(SDL_Rect bird, int ground)
{
	if (bird.y + bird.h >= ground) {
		return 1;
	} else if (bird.x + bird.w >= pipes[1][0] && bird.x + bird.w < pipes[1][0] + 80) {
		int res = collide_pipe(bird, 1);
		return res;
	} else if (bird.x <= pipes[1][0] + 80 && bird.x > pipes[1][0]){
		int res = collide_pipe(bird, 1);
		return res;
	} else {
		return 0;
	}
	
}


void move_bird_up(int old_y, int new_y, int x, long time, SDL_Texture *bird, SDL_Rect rec)
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
		renderTextureWH(bird, renderer, x, y, BIRD_WIDTH, BIRD_HEIGHT);
		SDL_RenderPresent(renderer);
		SDL_Delay(1000/FPS);
		rec.y = y;
		if (bird_collided(rec, 550) != 0) {
			printf("bird is dead\n");
			exit(EXIT_SUCCESS);
		}
	}
}
