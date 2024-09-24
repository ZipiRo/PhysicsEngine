#include <SFML/System/Vector2.hpp>
#include <LinkedList.h>

#include "Vector2D.h"
#include "Transform.h"
#include "VectorMath.h"
#include "Collisions.h"

namespace plain 
{
    void ProjectVertices(plain::Vector2D *vertices, plain::Vector2D axis, float &min, float &max)
    {
        min = 1000000000.0f;
        max = -1000000000.0f;

        for (int i = 0; i < 4; i++)
        {
            plain::Vector2D v = vertices[i];
            float projection = vectormath::DotProduct(v, axis);
            
            if(projection < min) min = projection;
            if(projection > max) max = projection;   
        }
    }

    bool collisions::IntersectPolygons(plain::Vector2D* verticesA, plain::Vector2D* verticesB)
    {
        for(int i = 0; i < 4; i++)
        {
            Vector2D nodeA = verticesA[i];
            Vector2D nodeB = verticesA[(i + 1) % 4];

            Vector2D vertex = nodeB - nodeA;
            Vector2D axis = Vector2D(vertex.y, -vertex.x);

            float minA, minB, maxA, maxB;
            ProjectVertices(verticesA, axis, minA, maxA);
            ProjectVertices(verticesB, axis, minB, maxB);

            if(minA >= maxB || minB >= maxA)
            {
                return false;
            }
        }

        for(int i = 0; i < 4; i++)
        {
            Vector2D nodeA = verticesB[i];
            Vector2D nodeB = verticesB[(i + 1) % 4];

            Vector2D vertex = nodeB - nodeA;
            Vector2D axis = Vector2D(vertex.y, -vertex.x);

            float minA, minB, maxA, maxB;
            ProjectVertices(verticesB, axis, minB, maxB);
            ProjectVertices(verticesA, axis, minA, maxA);

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