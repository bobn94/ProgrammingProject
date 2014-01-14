/*#include <SDL_image.h>
#pragma comment(lib,"sdl2_image.lib")
#include <SDL_mixer.h>
#pragma comment (lib,"sdl2_mixer.lib")*/

#include "StateManager.h"

/*#include "MenuState.h"
#include "GameState.h"
#include "OptionsState.h"*/

#include "Engine.h"

int main(int argv, char *argc[]) {
	
	/*StateManager mgr;
	mgr.Attach(new MenuState());
	mgr.Attach(new GameState());
	mgr.Attach(new OptionsState());
	mgr.SetState("MenuState");

	while (mgr.IsRunning()) {
		mgr.Update(0.01f);
		mgr.Draw();
	};*/


	Engine engine;
	if(engine.Initialize()) {
		engine.Run();
	};
	engine.Cleanup();
};
