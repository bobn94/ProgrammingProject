#include "Collider.h"
#include "DuckObject.h"
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
bool Collider::Overlap(Collider *map, Vector2 origo1, float radius1, Vector2 &offset)
{
	//Circle vs Box Collision
    for (int j = 0; j < 4; j++)
    {
        //hämta startpunkten
			
        Vector2 A;
        //hämta slutpunkten
        Vector2 B;
        if (j==0)
        {
			A = map->m_position;
			B = Vector2(map->m_position.m_x, map->m_position.m_x + map->m_extention.m_x);
        }
        else if(j == 1)
        {
            A = Vector2(map->m_position.m_x, map->m_position.m_x + map->m_extention.m_x);
			B = Vector2(map->m_position.m_x + map->m_extention.m_x, map->m_position.m_x + map->m_extention.m_x);
        }
		else if(j == 2){
			A = Vector2(map->m_position.m_x + map->m_extention.m_x, map->m_position.m_x + map->m_extention.m_x);
			B = Vector2(map->m_position.m_x + map->m_extention.m_x, map->m_position.m_x);
		}
		else if(j == 3){
			A = Vector2(map->m_position.m_x + map->m_extention.m_x, map->m_position.m_x);
			B = map->m_position;
		}
        Vector2 C = origo1;
            
        //räkna ut avstånden mellan punkterna
        Vector2 f = A - C;
        Vector2 t = B - C;
        Vector2 l = t - f;
            
            
        float a = l.m_x * l.m_x + l.m_x * l.m_x ;
        float b = 2*(l.m_x * f.m_x + l.m_x * f.m_x) ;
        float c = f.m_x * f.m_x + f.m_x * f.m_x - radius1*radius1 ;
            
        float discriminant = b*b-4*a*c;
        if( discriminant < 0 )
        {
            continue;
        }
        else
        {
            discriminant = sqrt( discriminant );
                
            // cirkeln kan penetreras på två olika punkter, ingångspunkten och utgångspunkten
            float t1 = (-b - discriminant)/(2*a);
            float t2 = (-b + discriminant)/(2*a);
                
            // om t1 och t2 är mellan 0 och 1 har linjen gått igenom cirkeln
            // om t1 eller t2 är mellan 0 och 1 har linjen gått in i men inte igenom cirkeln
            if( t1 >= 0 && t1 <= 1 )
            {
				if(j == 0){
					offset.m_x -= 1;
				}
				else if(j == 1){
					offset.m_x += 1;
				}
				else if(j == 2){
					offset.m_x += 1;
				}
				else if(j == 3){
					offset.m_x -= 1;
				}
                return true ;
					
            }
            if( t2 >= 0 && t2 <= 1 )
            {
				if(j == 0){
					offset.m_x -= 1;
				}
				else if(j == 1){
					offset.m_x += 1;
				}
				else if(j == 2){
					offset.m_x += 1;
				}
				else if(j == 3){
					offset.m_x -= 1;
				}
                return true ;
            }
            //om t1 och t2 är större än 1 eller mindre än 0 har linjen missat cirkeln helt
        }
            
    }
    
    //har den gått igenom alla former och kommit till slutet har ingen kollision sket mellan några punkter
    return false;
	
}