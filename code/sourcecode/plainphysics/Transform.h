#pragma once
#include <cmath>

#include "Vector2D.h"

namespace PlainPhysics
{
    class Transform
    {
        public:
            Vector2D position;
            float sin;
            float cos;

            Transform();
            Transform(Vector2D position, float angle);
            Transform(float x, float y, float angle);
    };
}