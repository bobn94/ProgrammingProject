#pragma once

class Vector2 {
public:
	Vector2();
	Vector2(const Vector2 &rhs);
	Vector2(float x, float y);

	Vector2 &operator=(const Vector2 &rhs);
	Vector2 &operator+=(const Vector2 &rhs);
	Vector2 &operator-=(const Vector2 &rhs);
	Vector2 &operator*=(float value);
	Vector2 &operator/=(float value);

	Vector2 operator+(const Vector2 &rhs);
	Vector2 operator-(const Vector2 &rhs);
	Vector2 operator*(float value);
	Vector2 operator/(float value);

	bool operator==(const Vector2 &rhs);
	bool operator!=(const Vector2 &rhs);

	float Length();
	void Normalize();

	float m_x;
	float m_y;
};
