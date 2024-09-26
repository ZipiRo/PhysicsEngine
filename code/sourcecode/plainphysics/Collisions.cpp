#include <SFML/System/Vector2.hpp>
#include <list>

#include "Vector2D.h"
#include "Transform.h"
#include "VectorMath.h"
#include "Collisions.h"

namespace plain 
{
    void ProjectVertices(std::list<Vector2D>vertices, plain::Vector2D axis, float &min, float &max)
    {
        min = 1000000000.0f;
        max = -1000000000.0f;

        for (Vector2D v : vertices)
        {
            float projection = vectormath::DotProduct(v, axis);
            
            if(projection < min) min = projection;
            if(projection > max) max = projection;   
        }
    }

    bool collisions::IntersectPolygons(std::list<Vector2D>verticesA, std::list<Vector2D>verticesB)
    {
        for(auto vertex = verticesA.begin(); vertex != verticesA.end(); ++vertex)
        {
            Vector2D vertexA = *vertex++;
            Vector2D vertexB = (vertex == --verticesA.end()) ? verticesA.front() : *(vertex);

            Vector2D edge = vertexB - vertexA;
            Vector2D axis = Vector2D(edge.y, -edge.x);

            float minA, minB, maxA, maxB;
            ProjectVertices(verticesA, axis, minA, maxA);
            ProjectVertices(verticesB, axis, minB, maxB);

            if(minA >= maxB || minB >= maxA)
            {
                return false;
            }
        }

        for(auto vertex = verticesB.begin(); vertex != verticesB.end(); ++vertex)
        {
            Vector2D vertexA = *vertex++;
            Vector2D vertexB = (vertex == --verticesB.end()) ? verticesB.front() : *(vertex);

            Vector2D edge = vertexB - vertexA;
            Vector2D axis = Vector2D(edge.y, -edge.x);

            float minA, minB, maxA, maxB;
            ProjectVertices(verticesA, axis, minA, maxA);
            ProjectVertices(verticesB, axis, minB, maxB);

            if(minA >= maxB || minB >= maxA)
            {
                return false;
            }
        }

        return true;
    }

    bool collisions::IntersectCircles(Vector2D centerA, float radiusA, Vector2D centerB, float radiusB, 
            Vector2D &normal, float &depth) 
    {
        normal = Vector2D().Zero();
        depth = 0.0f;

        float distance = vectormath::Distance(centerA, centerB);
        float radiI = radiusA + radiusB;

        if(distance >= radiI)
        {
            return false;
        }

        normal = vectormath::Normalize(centerB - centerA);
        depth = radiI - distance;

        return true;
    }
}