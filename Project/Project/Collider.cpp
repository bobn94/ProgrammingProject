#include "Collider.h"
#include "PlayerObject.h"
#include <cmath>

Collider::Collider()
	:m_position(0.0f, 0.0f)
,m_extention(0.0f, 0.0f)
{

}

Collider::Collider(const Vector2 &position, const Vector2 &extention)
	:m_position(position)
	,m_extention(extention){

	}

	bool Collider::Overlap(Collider &other, Vector2 &offset){
		float A = m_extention.m_x * 0.5f;
		float B = other.m_extention.m_x * 0.5f;
		float C = (m_position.m_x + A) - (other.m_position.m_x + B);

		if(fabs(C) < A + B){
			float Q = m_extention.m_y * 0.5f;
			float P = other.m_extention.m_y * 0.5f;
			float Z = (m_position.m_y + Q) - (other.m_position.m_y + P);
			if(fabs(Z) <= Q + P){
				float dx = fabs(C) - (A+B);
				float dy = fabs(Z) - (Q+P);
				if(dx >= dy && dy < -1)
				{
					if(m_position.m_x < other.m_position.m_x)
						{
							offset.m_x = -dx;
							other.m_position.m_x += -dx;
						}
						else

						{
							offset.m_x = dx;
							other.m_position.m_x += dx;
						}
				}
 				else
					{
						if(m_position.m_y < other.m_position.m_y)
						{
							offset.m_y = -dy;
							other.m_position.m_y += -dy;
						}
						else

						{
							offset.m_y = dy;
							other.m_position.m_y += dy;
						}
    
					
					}
				
				
				return true;
			}
		}
		return false;
	}