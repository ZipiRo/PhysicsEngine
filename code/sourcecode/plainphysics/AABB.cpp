#include "AABB.h"

namespace PlainPhysics
{
    AABB::AABB () 
    {
        this->min = Vector2D(0, 0);
        this->max = Vector2D(0, 0);
    }

    AABB::AABB (Vector2D min, Vector2D max)
    {
        this->min = min;
        this->max = max;
    }

    AABB::AABB (float minX, float minY, float maxX, float maxY)
    {
        this->min = Vector2D(minX, minY);
        this->max = Vector2D(maxX, maxY);
    }
}
