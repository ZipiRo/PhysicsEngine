#include <SFML/System/Vector2.hpp>
#include <Vector2D.hpp>

#include "Collisions.hpp"

namespace Plain
{
    bool IntersectCircles(Vector2D centerA, float radiusA, Vector2D centerB, float radiusB, 
            Vector2D &normal, float &depth){

        normal = Vector2D().Zero();
        depth = 0.0f;

        float distance = Distance(centerA, centerB);
        float radiI = radiusA + radiusB;

        if(distance >= radiI)
        {
            return false;
        }

        normal = Normalize(centerB - centerA);
        depth = radiI - distance;

        return true;
    }
}