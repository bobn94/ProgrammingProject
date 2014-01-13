#include <cmath>
#include "Vector2.h"

Vector2::Vector2() {
	m_x = 0.0f;
	m_y = 0.0f;
};

Vector2::Vector2(const Vector2 &rhs) {
	m_x = rhs.m_x;
	m_y = rhs.m_y;
};

Vector2::Vector2(float x, float y) {
	m_x = x;
	m_y = y;
};

Vector2 &Vector2::operator=(const Vector2 &rhs) {
	this->m_x = rhs.m_x;
	this->m_y = rhs.m_y;
	return *this;
};

Vector2 &Vector2::operator+=(const Vector2 &rhs) {
	m_x += rhs.m_x;
	m_y += rhs.m_y;
	return *this;
};

Vector2 &Vector2::operator-=(const Vector2 &rhs) {
	m_x -= rhs.m_x;
	m_y -= rhs.m_y;
	return *this;
};

Vector2 &Vector2::operator*=(float value) {
	m_x *= value;
	m_y *= value;
	return *this;
};

Vector2 &Vector2::operator/=(float value) {
	m_x /= value;
	m_y /= value;
	return *this;
};

Vector2 Vector2::operator+(const Vector2 &rhs) {
	return Vector2(m_x + rhs.m_x, m_y + rhs.m_y);
};

Vector2 Vector2::operator-(const Vector2 &rhs) {
	return Vector2(m_x - rhs.m_x, m_y - rhs.m_y);
};

Vector2 Vector2::operator*(float value) {
	return Vector2(m_x * value, m_y * value);
};

Vector2 Vector2::operator/(float value) {
	return Vector2(m_x / value, m_y / value);
};

bool Vector2::operator==(const Vector2 &rhs) {
	const float epsilon = 0.00001f;
	return fabs(m_x - rhs.m_x) < epsilon && fabs(m_y - rhs.m_y) < epsilon;
};

bool Vector2::operator!=(const Vector2 &rhs) {
	return !(*this == rhs);
};

float Vector2::Length() {
	return sqrtf(m_x * m_x + m_y * m_y);
};

void Vector2::Normalize() {
	float length = Length();
	if(length > 0.0f) {
		m_x /= length;
		m_y /= length;
	};
};
