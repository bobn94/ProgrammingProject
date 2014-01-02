
#pragma once

class Vector2{
public:
	Vector2();
	Vector2(const Vector2 &rhs);
	Vector2(const float x, float y);
	float Lenght();
	void Normalize();
	
	Vector2 &operator=(const Vector2 &rhs);
	Vector2 &operator+=(const Vector2 &rhs);
	Vector2 &operator-=(const Vector2 &rhs);
	Vector2 &operator*=(float value);
	Vector2 &operator/=(float value);
	bool operator==(const Vector2 &rhs);
	bool operator!=(const Vector2 &rhs);

	Vector2 operator-(const Vector2 &rhs);
	Vector2 operator+(const Vector2 &rhs);
	Vector2 operator*(float value);
	Vector2 operator/(float value);

	float m_x;
	float m_y;

};