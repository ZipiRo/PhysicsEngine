#include "Manifold.h"

namespace PlainPhysics
{
    Manifold::Manifold(Body *bodyA, Body *bodyB, Vector2D normal, float depth, Vector2D contactOne, Vector2D contactTwo, int contactCount)
    {
        this->bodyA = bodyA;
        this->bodyB = bodyB;
        this->normal = normal;
        this->depth = depth;
        this->contactOne = contactOne;
        this->contactTwo = contactTwo;
        this->contactCount = contactCount;
    }
}