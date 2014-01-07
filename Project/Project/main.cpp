#include <SDL.h>
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "sdl2main.lib")
#include <SDL_image.h>
#pragma comment(lib, "sdl2_image.lib")
#include <SDL_mixer.h>
#pragma comment(lib, "sdl2_mixer.lib")

#include "Engine.h"

int main(int argc, char *argv[]) {
	Engine engine;
	if(engine.Initialize()) {
		engine.Run();
	};
	engine.Cleanup();


	return 0;
};
