#include <cmath>

#include "Vector2D.h"
#include "Transform.h"

Plain::Transform::Transform() 
{
    this->position = Plain::Vector2D().Zero();
    this->cos = 0;
    this->sin = 0;
}

Plain::Transform::Transform(Plain::Vector2D position, float angle)
{
    this->position = position;
    this->sin = sinf(angle * 3.141592f / 180);
    this->cos = cosf(angle * 3.141592f / 180);
}

Plain::Transform::Transform(float x, float y, float angle)
{
    this->position = Plain::Vector2D(x, y);
    this->sin = sinf(angle * 3.141592f / 180);
    this->cos = cosf(angle * 3.141592f / 180);
}
