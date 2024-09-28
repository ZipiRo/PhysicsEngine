#include <SFML/System/Vector2.hpp>
#include <cmath>
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

    Vector2D FindArithmeticMEan(std::list<Vector2D> vertices)
    {
        float sumX = 0.0f, sumY = 0.0f;
        
        for(Vector2D v : vertices)
        {
            sumX += v.x;
            sumY += v.y;
        }

        return Vector2D(sumX / (float)vertices.size(), sumY / (float)vertices.size());
    }

    bool collisions::IntersectPolygons(std::list<Vector2D>verticesA, std::list<Vector2D>verticesB, Vector2D &normal, float &depth)
    {
        normal = Vector2D().Zero();
        depth = 1000000000.0f;

        for(auto vertex = verticesA.begin(); vertex != verticesA.end(); ++vertex)
        {
            Vector2D vertexA = *(vertex);
            Vector2D vertexB = *(++vertex);

            Vector2D edge = vertexB - vertexA;
            Vector2D axis = Vector2D(edge.y, -edge.x);

            float minA, minB, maxA, maxB;
            ProjectVertices(verticesA, axis, minA, maxA);
            ProjectVertices(verticesB, axis, minB, maxB);

            if(minA >= maxB || minB >= maxA)
            {
                return false;
            }

            float axisDepth = std::min(maxB - minA, maxA - minB);

            if(axisDepth < depth) 
            {
                depth = axisDepth;
                normal = axis;
            }
        }

        for(auto vertex = verticesB.begin(); vertex != verticesB.end(); ++vertex)
        {
            Vector2D vertexA = *vertex++;
            Vector2D vertexB = *(++vertex);

            Vector2D edge = vertexB - vertexA;
            Vector2D axis = Vector2D(edge.y, -edge.x);

            float minA, minB, maxA, maxB;
            ProjectVertices(verticesA, axis, minA, maxA);
            ProjectVertices(verticesB, axis, minB, maxB);

            if(minA >= maxB || minB >= maxA)
            {
                return false;
            }

            float axisDepth = std::min(maxB - minA, maxA - minB);

            if(axisDepth < depth) 
            {
                depth = axisDepth;
                normal = axis;
            }
        }

        depth /= vectormath::Length(normal);
        normal = vectormath::Normalize(normal);

        Vector2D centerA = FindArithmeticMEan(verticesA);
        Vector2D centerB = FindArithmeticMEan(verticesB);

        Vector2D direction = centerB - centerA;

        if(vectormath::DotProduct(direction, normal) < 0.0f)
        {
            normal = (normal * -1.0f);
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