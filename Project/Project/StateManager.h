#pragma once
#include <vector>

class State;

class StateManager {
public:
	StateManager();
	~StateManager();

	 void Attach(State *state);
	 void Update(float deltatime);
	 void Draw();
	 void SetState(const std::string &type);
	 void ChangeState();
	 bool IsRunning();

private:
	std::vector<State*> m_states;
	State *m_current;
};