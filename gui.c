#include <stdio.h>
#include "SDL_Error.h"
#include "SDL_Texture.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


extern int point;
extern SDL_Renderer *renderer;

TTF_Font *font = NULL;
SDL_Surface *font_surface = NULL;
SDL_Texture *font_texture = NULL;
const int FONT_SIZE = 42;

SDL_Color color = {0, 0, 0, 0};


void update_points()
{
	char points[20];
	sprintf(points, "score: %d", point);
	font_surface = TTF_RenderText_Blended(font, points, color);
	if (font_surface == NULL)
		SDL_ErrorExit("TTF_RenderText_Blended");

	font_texture = SDL_CreateTextureFromSurface(renderer, font_surface);
	if (font_texture == NULL)
		SDL_ErrorExit("Could not create font texture");

	SDL_FreeSurface(font_surface);
}

int init_gui(void)
{
	if (TTF_Init() != 0)
		SDL_ErrorExit("TTF_Init failure");

	font = TTF_OpenFont("resources/font.ttf", FONT_SIZE);
	if (font == NULL)
		SDL_ErrorExit("Could not open font");
	
	update_points();
	
	return 0;
}

void render_gui()
{
	renderTexture(font_texture, renderer, 50, 30);
}

