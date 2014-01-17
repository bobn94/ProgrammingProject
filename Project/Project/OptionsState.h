#pragma once

#include "State.h"

class OptionsState : public State {
public:
	OptionsState();

	bool Enter();
	void Exit();
	bool Update(float deltatime);
	void Draw();
	std::string Next();
	bool IsType(const std::string &type);

private:

};
