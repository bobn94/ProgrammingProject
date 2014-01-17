#pragma once

#include "State.h"

class GameStateB : public State {
public:
	GameStateB();

	bool Enter();
	void Exit();
	bool Update(float deltatime);
	void Draw();
	std::string Next();
	bool IsType(const std::string &type);

private:

};

