
#pragma once

#include "Vector2.h"
class Collider;
class Sprite;

class GameObject{
public:
	GameObject(Sprite *sprite = nullptr, Collider *collider = nullptr, int flag = 0);

	const Vector2 &GetPosition() const;
	void SetPosition(const Vector2 &position);
	bool HasSprite() const;
	Sprite* GetSprite();
	bool HasCollider() const;
	Collider* GetCollider();

protected:
	Vector2 m_position;
	Sprite* m_sprite;
	Collider *m_collider;
	int m_flag;// flagga för att kunna välja om ett object ska få en collider eller inte
};