#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "SDL_Error.h"

extern SDL_Texture *background;

SDL_Texture *loadTexture(char *file, SDL_Renderer *renderer)
{
	SDL_Texture *texture = NULL;
	texture = IMG_LoadTexture(renderer, file);
	if (texture == NULL)
		SDL_ErrorExit("could not load texture");	

	return texture;
}

void renderTextureWH(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y,
		int w, int h)
{
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	dest.w = w;
	dest.h = h;

	SDL_RenderCopy(renderer, texture, NULL, &dest);	
}

void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y)
{
	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	renderTextureWH(texture, renderer, x, y, w, h);
}

void render_background(SDL_Renderer *renderer)
{
	int x, y, h, w;
	SDL_QueryTexture(background, NULL, NULL, &w, &h);
	x = 0;
	y = 0;
	
	for (; x <= 1000; x += w) {
		renderTexture(background, renderer, x, y);
	}
}
