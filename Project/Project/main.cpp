<<<<<<< HEAD
#include <SDL.h>
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "sdl2main.lib")
#include <SDL_image.h>
#pragma comment(lib, "sdl2_image.lib")
#include <SDL_mixer.h>
#pragma comment(lib, "sdl2_mixer.lib")

int main(int argv, char *argc[]){
=======
#include "Engine.h"

int main(int argc, char *argv[]) {
	Engine engine;
	if(engine.Initialize()) {
		engine.Run();
	};
	engine.Cleanup();
>>>>>>> a4898c2af16098eeed8b892b1188d59662d4757d

	return 0;
};
