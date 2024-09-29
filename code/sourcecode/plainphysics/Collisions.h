#pragma once

namespace PlainPhysics
{
    namespace collisions
    {
        bool IntersectCircles(Vector2D centerA, float radiusA, Vector2D centerB, float radiusB, 
            Vector2D &normal, float &depth);
        bool IntersectPolygons(std::list<Vector2D>verticesA, Vector2D centerA,  std::list<Vector2D>verticesB, Vector2D centerB, 
            Vector2D &normal, float &depth);
        bool IntersectCirclesPolygons(Vector2D circleCenter, float radius, std::list<Vector2D>vertices, Vector2D polygonCenter,
            Vector2D &normal, float &depth);
    }
}