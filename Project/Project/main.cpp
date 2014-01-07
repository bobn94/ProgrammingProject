/*#include <SDL_image.h>
#pragma comment(lib,"sdl2_image.lib")
#include <SDL_mixer.h>
#pragma comment (lib,"sdl2_mixer.lib")*/

#include "Engine.h"

int main(int argv, char *argc[]) {
	Engine engine;
	if(engine.Initialize()) {
		engine.Run();
	};
	engine.Cleanup();
};
