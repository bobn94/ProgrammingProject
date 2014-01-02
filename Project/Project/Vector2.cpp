#include <cmath>
#include "Vector2.h"

Vector2::Vector2(){
	m_x = 0.0f;
	m_y = 0.0f;
}
	Vector2::Vector2(const Vector2 &rhs){
		m_x = rhs.m_x;
		m_y = rhs.m_y;
	}
	Vector2::Vector2(const float x, float y){
		m_x = x;
		m_y = y;
	}
	float Vector2::Lenght(){
		return sqrtf(m_x * m_x + m_y * m_y);
	}
	void Vector2::Normalize(){
		float lenght = Lenght();
		if(lenght > 0.0f){
			m_x /= lenght;
			m_y /= lenght;
		}
	}
	Vector2 &Vector2::operator=(const Vector2 &rhs){
		m_x = rhs.m_x;
		m_y = rhs.m_y;
		return *this;
	}
	Vector2 &Vector2::operator+=(const Vector2 &rhs){
		m_x += rhs.m_x;
		m_y += rhs.m_y;
		return *this;
	}
	Vector2 &Vector2::operator-=(const Vector2 &rhs){
		m_x -= rhs.m_x;
		m_y -= rhs.m_y;
		return *this;
	}
	Vector2 &Vector2::operator*=(float value){
		m_x *= value;
		m_y *= value;
		return *this;
	}
	Vector2 &Vector2::operator/=(float value){
		m_x /= value;
		m_y /= value;
		return *this;
	}
	
	bool Vector2::operator==(const Vector2 &rhs){
		const float epsilon = 0.00001f;
		return fabs(m_x -rhs.m_x) < epsilon && fabs(m_y - rhs.m_x) < epsilon;
	}
	bool Vector2::operator!=(const Vector2 &rhs){
		return !(*this == rhs);
	}
	Vector2 Vector2::operator+(const Vector2 &rhs){
		return Vector2(m_x + rhs.m_x, m_y + rhs.m_y);
	}
	Vector2 Vector2::operator-(const Vector2 &rhs){
		return Vector2(m_x - rhs.m_x, m_y - rhs.m_y);
	}
	Vector2 Vector2::operator*(float value){
		return Vector2(m_x * value, m_y * value);
	}
	Vector2 Vector2::operator/(float value){
		return Vector2(m_x / value, m_y / value);
	}