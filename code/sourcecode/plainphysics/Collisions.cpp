#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <list>

#include "Vector2D.h"
#include "Transform.h"
#include "VectorMath.h"
#include "Collisions.h"

namespace PlainPhysics 
{
    void ProjectVertices(std::list<Vector2D>vertices, Vector2D axis, float& min, float& max)
    {
        min = 1000000.000f;
		max = -1000000.000f;

        for (Vector2D v : vertices)
        {
            float projection = vectormath::DotProduct(v, axis);
            
            if(projection < min) min = projection;
            if(projection > max) max = projection;   
        }
    }
    void ProjectCircle(Vector2D center, float radius, Vector2D axis, float& min, float& max)
    {
        Vector2D direction = vectormath::Normalize(axis);
        Vector2D directionRadius = direction * radius;

        Vector2D point1 = center + directionRadius;
        Vector2D point2 = center - directionRadius;

        min = vectormath::DotProduct(point1, axis);
        max = vectormath::DotProduct(point2, axis);

        if(min > max)
        {
            float aux = min;
            min = max;
            max = aux;
        }
    }
    int ClosestPointOnPolygon(Vector2D center, std::list<Vector2D> vertices)
    {
        int result = -1, i = 0;
        float minDistance = 1000000.000f;


        for(Vector2D v : vertices)
        {
            i++;
            float distance = vectormath::Distance(v, center);

            if(distance < minDistance)
            {
                minDistance = distance;
                result = i;
            }
        }      

        return result;
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

    bool collisions::IntersectPolygons(std::list<Vector2D>verticesA, Vector2D centerA, std::list<Vector2D>verticesB, Vector2D centerB, 
        Vector2D &normal, float &depth)
    {
        normal = Vector2D().Zero();
        depth = 1000000.0f;

        for(auto vertex = verticesA.begin(); vertex != verticesA.end(); ++vertex)
        {
            Vector2D vertexA = *(vertex);
            Vector2D vertexB = *(++vertex);

            Vector2D edge = vertexB - vertexA;
            Vector2D axis = Vector2D(-edge.y, edge.x);
            axis = vectormath::Normalize(axis);

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
            Vector2D axis = Vector2D(-edge.y, edge.x);
            axis = vectormath::Normalize(axis);

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

        Vector2D direction = centerB - centerA;

        if(vectormath::DotProduct(direction, normal) < 0.0f)
        {
            normal = (normal * -1.0f);
        }

        return true;
    }

    bool collisions::IntersectCirclesPolygons(Vector2D circleCenter, float radius, std::list<Vector2D>vertices, Vector2D polygonCenter,
        Vector2D &normal, float &depth)
    {
        normal = Vector2D().Zero();
        depth = 1000000.000f;

        for(auto vertex = vertices.begin(); vertex != vertices.end(); ++vertex)
        {
            Vector2D vertexA = *(vertex);
            Vector2D vertexB = *(++vertex);

            Vector2D edge = vertexB - vertexA;
            Vector2D axis = Vector2D(-edge.y, edge.x);
            axis = vectormath::Normalize(axis);

            float minA, minB, maxA, maxB;
            ProjectVertices(vertices, axis, minA, maxA);
            ProjectCircle(circleCenter, radius, axis, minB, maxB);

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

        int closestPoint_Index = ClosestPointOnPolygon(circleCenter, vertices);

        int index = 0; Vector2D closestPoint;
        for(Vector2D v : vertices)
            if(closestPoint_Index == ++index) { closestPoint = v; break; }

        Vector2D axis = closestPoint - circleCenter;
        axis = vectormath::Normalize(axis);

        float minA, minB, maxA, maxB;
        ProjectVertices(vertices, axis, minA, maxA);
        ProjectCircle(circleCenter, radius, axis, minB, maxB);

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

        Vector2D direction = polygonCenter - circleCenter;

        if(vectormath::DotProduct(direction, normal) < 0.0f)
        {
            normal = (normal * -1.0f);
        }

        return true;
    }
}