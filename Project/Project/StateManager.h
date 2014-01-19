#pragma once
#include <vector>

class State;
class DrawManager;
class SpriteManager;

class StateManager {
public:
	StateManager();
	~StateManager();

	 void Attach(State *state);
	 void Update(float deltatime, SpriteManager* m_sprite_manager);
	 void Draw(DrawManager* m_draw_manager);
	 void SetState(const std::string &type);
	 void ChangeState();
	 bool IsRunning();

	 State *m_current;
private:
	std::vector<State*> m_states;
	
};