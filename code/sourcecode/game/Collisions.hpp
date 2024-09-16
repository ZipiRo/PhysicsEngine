#pragma once

namespace Plain
{
    bool IntersectCircles(Vector2D centerA, float radiusA, Vector2D centerB, float radiusB, 
        Vector2D &normal, float &depth);
}