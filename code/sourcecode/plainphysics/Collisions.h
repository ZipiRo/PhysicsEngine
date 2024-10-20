#pragma once
#include <cmath>
#include <vector>

#include "Vector2D.h"
#include "Transform.h"
#include "VectorMath.h"
#include "AABB.h"

namespace PlainPhysics
{
    namespace Collisions
    {
        bool IntersectAABB(AABB a, AABB b);

        bool IntersectCircles(Vector2D centerA, float radiusA, Vector2D centerB, float radiusB, 
            Vector2D &normal, float &depth);
        bool IntersectPolygons(std::vector<Vector2D>verticesA, Vector2D centerA,  std::vector<Vector2D>verticesB, Vector2D centerB, 
            Vector2D &normal, float &depth);
        bool IntersectCirclesPolygons(Vector2D circleCenter, float radius, std::vector<Vector2D>vertices, Vector2D polygonCenter,
            Vector2D &normal, float &depth);
        
        void FindCircleContactPoint(Vector2D centerA, float radiusA, Vector2D centerB, Vector2D& contactPoint);
        void FindCirclePolygonContactPoint(Vector2D circleCenter, float radius, std::vector<Vector2D>vertices, Vector2D polygonCenter, Vector2D& contactPoint);
        void FindPolygonsContactPoints(std::vector<Vector2D>verticesA, std::vector<Vector2D>verticesB, Vector2D& contactOne, Vector2D& contactTwo, int& contactCount);
    }
}