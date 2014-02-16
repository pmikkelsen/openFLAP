#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

void SDL_PrintError(char *msg)
{
	printf("%s: %s\n", msg, SDL_GetError());
}

void SDL_ErrorExit(char *msg)
{
	SDL_PrintError(msg);
	exit(EXIT_FAILURE);
}
