#pragma once

namespace Plain
{
    bool IntersectPolygons(Vector2D* verticesA, Vector2D* verticesB);
    bool IntersectCircles(Vector2D centerA, float radiusA, Vector2D centerB, float radiusB, 
        Vector2D &normal, float &depth);
}