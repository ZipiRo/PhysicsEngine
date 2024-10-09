#pragma once
#include "Vector2D.h"
#include "Body.h"

namespace PlainPhysics
{
    class Manifold
    {
        public:
            Body *bodyA;
            Body *bodyB;
            Vector2D normal;
            float depth;
            Vector2D contactOne;
            Vector2D contactTwo;
            int contactCount;

            Manifold(Body *bodyA, Body *bodyB, Vector2D normal, float depth, Vector2D contactOne, Vector2D contactTwo, int contactCount);
    };
}