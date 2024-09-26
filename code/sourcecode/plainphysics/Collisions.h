#pragma once

namespace plain
{
    namespace collisions
    {
        bool IntersectPolygons(std::list<Vector2D> verticesA, std::list<Vector2D> verticesB);
        bool IntersectCircles(Vector2D centerA, float radiusA, Vector2D centerB, float radiusB, 
            Vector2D &normal, float &depth);
    }
}