
#include "Sprite.h"
#include "GameObject.h"
//#include "Collider.h"

GameObject::GameObject(Sprite *sprite, Collider *collider, int flag)
:m_sprite(sprite)
,m_collider(collider)
,m_flag(flag)
{
	
}

	const Vector2 &GameObject::GetPosition(){
		return m_position;
	}
	void GameObject::SetPosition(const Vector2 &position){
		m_position = position;
	}
	bool GameObject::HasSprite() const{
		return m_sprite;
	}
	Sprite* GameObject::GetSprite(){
		return m_sprite;
	}
	
	/*bool GameObject::HasCollider() const{
		
		return m_collider != nullptr;
	}
	Collider* GameObject::GetCollider(){
		return m_collider;
	}*/