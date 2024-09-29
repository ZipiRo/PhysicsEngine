#include <cmath>

#include "Vector2D.h"
#include "Transform.h"

namespace PlainPhysics
{
    transform::Transform::Transform() 
    {
        this->position = PlainPhysics::Vector2D().Zero();
        this->cos = 0;
        this->sin = 0;
    }

    transform::Transform::Transform(PlainPhysics::Vector2D position, float angle)
    {
        this->position = position;
        this->sin = sinf(angle * 3.141592f / 180);
        this->cos = cosf(angle * 3.141592f / 180);
    }

    transform::Transform::Transform(float x, float y, float angle)
    {
        this->position = PlainPhysics::Vector2D(x, y);
        this->sin = sinf(angle * 3.141592f / 180);
        this->cos = cosf(angle * 3.141592f / 180);
    }
}
