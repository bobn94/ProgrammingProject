
#include "Input.h"


KeyBoard::KeyBoard(){
	for(int i = 0; i < 256; i++){
		m_current[i] = false;
		m_previous[i] = false;
	}
}
bool KeyBoard::IsDown(int key){
	return m_current[key];
}
bool KeyBoard::IsDownOnce(int key){
	return m_current[key] && !m_previous[key];
}
void KeyBoard::PostUpdate(){
	for(int i = 0; i < 256; i++){
		m_previous[i] = m_current[i];
	}
}
Mouse::Mouse(){
	for(int i = 0; i < MB_COUNT; i++){
	m_current[i] = false;
	m_previous[i] = false;
	}
	m_x = 0;
	m_y = 0;
}
	int Mouse::GetX() const{
		return m_x;
	}
	int Mouse::GetY() const{
		return m_y;
	}
	bool Mouse::IsDown(EmouseButton button) const{
		return m_current[button];
	}
	bool Mouse::IsDownOnce(EmouseButton button) const{
		return m_current[button] && !m_previous[button];
	}
	void Mouse::PostUpdate(){
		for(int i = 0; i < MB_COUNT; i++){
		m_previous[i] = m_current[i];
	}
	}