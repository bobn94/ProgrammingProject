#include <string>
#include "State.h"

	int State::GetState(){
		return m_state;
	}
	std::string State::GetStateName(){
		return m_state_name;
	}
	bool State::SetState(int state){
		if(state == 0){
			m_state = state;
			m_state_name = "MenuState";
			return true;
		}
		else if(state == 1){
			m_state = state;
			m_state_name = "IntroState";
			return true;
		}
		else if(state == 2){
			m_state = state;
			m_state_name = "GameState";
			return true;
		}
		else{
			return false;
		}
	}