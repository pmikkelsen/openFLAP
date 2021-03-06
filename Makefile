CC = gcc

CFLAGS = -Wall -Wextra  
SDL_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

OBJECTS = main.o SDL_Error.o SDL_Texture.o move_bird.o ground_pipes.o gui.o
SOURCES = main.c SDL_Error.c SDL_Texture.c move_bird.c ground_pipes.c gui.c
HEADERS = SDL_Error.h SDL_Texture.h move_bird.h ground_pipes.h gui.h
EXEC = openFLAP
WIN_EXEC = builds/openFLAP.exe

all: $(EXEC) 


$(EXEC): $(OBJECTS) $(HEADERS)
	$(CC) $(OBJECTS) -o $@ $(SDL_FLAGS)

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
gui.o: gui.c gui.h
	$(CC) $(CFLAGS) -c $< -o $@

$(WIN_EXEC): $(SOURCES) $(HEADERS) 
	x86_64-w64-mingw32-gcc $(SOURCES) -lmingw32 -lSDL2main $(SDL_FLAGS) -mwindows -o $@

clean:
	rm $(OBJECTS)
	rm $(EXEC)
