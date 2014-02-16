CC = clang

CFLAGS = -Wall -Wextra  
SDL_FLAGS = -lSDL2 -lSDL2_image

OBJECTS = main.o SDL_Error.o SDL_Texture.o move_bird.o ground_pipes.o
HEADERS = SDL_Error.h SDL_Texture.h move_bird.h ground_pipes.h
EXEC = openFLAP


all: $(EXEC)


$(EXEC): $(OBJECTS) $(HEADERS)
	$(CC) $(OBJECTS) -o $@ $(SDL_FLAGS)
	./$@


main.o: main.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

SDL_Error.o: SDL_Error.c SDL_Error.h
	$(CC) $(CFLAGS) -c $< -o $@

SDL_Texture.o: SDL_Texture.c SDL_Texture.h
	$(CC) $(CFLAGS) -c $< -o $@

move_bird.o: move_bird.c move_bird.h
	$(CC) $(CFLAGS) -c $< -o $@

ground_pipes.o: ground_pipes.c ground_pipes.h 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJECTS)
	rm $(EXEC)
