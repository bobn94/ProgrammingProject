#include <string>

class State {

public:
	int GetState();
	std::string GetStateName();
	bool SetState(int state);
private:
	int m_state;
	std::string m_state_name;
};