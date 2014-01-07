
#pragma once
#include "Vector2.h"

class DuckObject;

class Collider{
public:
	Collider();
	Collider(const Vector2 &position, const Vector2 &extention);

	bool Overlap(Collider &other, Vector2 &offset);

	Vector2 m_position;
	Vector2 m_extention;

};