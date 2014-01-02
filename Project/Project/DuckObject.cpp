#include "DuckObject.h"

DuckObject::DuckObject(Sprite* sprite = nullptr) {
}

void DuckObject::AddAnimation(const std::string &name, Animation *sprite) {
	m_animations.insert(std::pair<std::string,Animation*>(name, sprite));
	if(m_sprite == nullptr) {
		m_sprite = sprite;
		m_current_animation = sprite;
	};
};
