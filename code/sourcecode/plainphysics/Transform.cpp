#include "Transform.h"
 
const float DEG_TO_RAD = 3.141592f / 180.0f;

namespace PlainPhysics
{
    Transform::Transform() 
    {
        this->position = Vector2D(0, 0);
        this->cos = 1.0f;
        this->sin = 0.0f;
    }

    Transform::Transform(Vector2D position, float angle)
    {
        this->position = position;
        this->sin = sinf(angle * DEG_TO_RAD);
        this->cos = cosf(angle * DEG_TO_RAD);
    }

    Transform::Transform(float x, float y, float angle)
    {
        this->position = Vector2D(x, y);
        
        this->sin = sinf(angle * DEG_TO_RAD);
        this->cos = cosf(angle * DEG_TO_RAD);
    }
}
