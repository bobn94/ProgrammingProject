#pragma once
#include <string>

class State {
public:
	virtual ~State() {};
	virtual bool Enter() = 0;
	virtual void Exit() = 0;
	virtual bool Update(float deltatime) = 0;
	virtual void Draw() = 0;
	virtual std::string Next() = 0;
	virtual bool IsType(const std::string &type) = 0;
};
