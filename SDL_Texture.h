SDL_Texture *loadTexture(char *file, SDL_Renderer *renderer);

void renderTextureWH(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y,
		int w, int h);

void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y);

void render_background(SDL_Renderer *renderer);
