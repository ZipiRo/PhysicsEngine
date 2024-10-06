#include <cmath>
#include <list>

#include "Vector2D.h"
#include "Transform.h"
#include "VectorMath.h"
#include "AABB.h"
#include "Collisions.h"

const float max_float = 1000000.0f;
const float min_float = -1000000.0f;

namespace PlainPhysics 
{
    void ProjectVertices(std::list<Vector2D>vertices, Vector2D axis, float& min, float& max)
    {
        min = max_float;
		max = min_float;

        for (Vector2D vertex : vertices)
        {
            float projection = VectorMath::DotProduct(vertex, axis);
            
            if(projection < min) min = projection;
            if(projection > max) max = projection;   
        }
    }

    void ProjectCircle(Vector2D center, float radius, Vector2D axis, float& min, float& max)
    {
        Vector2D direction = VectorMath::Normalize(axis);
        Vector2D directionRadius = direction * radius;

        Vector2D point1 = center + directionRadius;
        Vector2D point2 = center - directionRadius;

        min = VectorMath::DotProduct(point1, axis);
        max = VectorMath::DotProduct(point2, axis);

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
        float minDistance = max_float;


        for(Vector2D vertex : vertices)
        {
            i++;
            float distance = VectorMath::Distance(vertex, center);

            if(distance < minDistance)
            {
                minDistance = distance;
                result = i;
            }
        }      

        return result;
    }
    
    bool Collisions::IntersectAABB(AABB a, AABB b) {
		if (a.max.x <= b.min.x || b.max.x <= a.min.x) return false;
		if (a.max.y <= b.min.y || b.max.y <= a.min.y) return false;

		return true;
	}

    bool Collisions::IntersectCircles(Vector2D centerA, float radiusA, Vector2D centerB, float radiusB, 
            Vector2D &normal, float &depth) 
    {
        normal = Vector2D(0, 0);
        depth = 0.0f;

        float distance = VectorMath::Distance(centerA, centerB);
        float radiI = radiusA + radiusB;

        if(distance >= radiI)
        {
            return false;
        }

        normal = VectorMath::Normalize(centerB - centerA);
        depth = radiI - distance;

        return true;
    }

    bool Collisions::IntersectPolygons(std::list<Vector2D>verticesA, Vector2D centerA, std::list<Vector2D>verticesB, Vector2D centerB, 
        Vector2D &normal, float &depth)
    {
        normal = Vector2D(0, 0);
        depth = max_float;
        
        Vector2D axis = Vector2D(0, 0);
        float minA, minB, maxA, maxB;
        
        for(auto vertex = verticesA.begin(); vertex != verticesA.end(); ++vertex)
        {
            auto next_vertex = std::next(vertex);
            if(next_vertex == verticesA.end())
                next_vertex = verticesA.begin(); 

            Vector2D vertexA = *vertex;
            Vector2D vertexB = *next_vertex;

            Vector2D edge = vertexB - vertexA;
            axis = Vector2D(edge.y, -edge.x);
            axis = VectorMath::Normalize(axis);

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
            auto next_vertex = std::next(vertex);
            if(next_vertex == verticesA.end())
                next_vertex = verticesA.begin(); 

            Vector2D vertexA = *vertex;
            Vector2D vertexB = *next_vertex;

            Vector2D edge = vertexB - vertexA;
            axis = Vector2D(edge.y, -edge.x);
            axis = VectorMath::Normalize(axis);

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

        if(VectorMath::DotProduct(direction, normal) < 0.0f)
        {
            normal = -normal;
        }

        return true;
    }

    bool Collisions::IntersectCirclesPolygons(Vector2D circleCenter, float radius, std::list<Vector2D>vertices, Vector2D polygonCenter,
        Vector2D &normal, float &depth)
    {
        normal = Vector2D(0, 0);
        depth = max_float;

        Vector2D axis = Vector2D(0, 0);
        float minA, minB, maxA, maxB;

        for(auto vertex = vertices.begin(); vertex != vertices.end(); ++vertex)
        {
            
            auto next_vertex = std::next(vertex);
            if(next_vertex == vertices.end())
                next_vertex = vertices.begin(); 

            Vector2D vertexA = *vertex;
            Vector2D vertexB = *next_vertex;

            Vector2D edge = vertexB - vertexA;
            axis = Vector2D(edge.y, -edge.x);
            axis = VectorMath::Normalize(axis);

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

        axis = closestPoint - circleCenter;
        axis = VectorMath::Normalize(axis);

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

        if(VectorMath::DotProduct(direction, normal) < 0.0f)
        {
            normal = -normal;
        }

        return true;
    }
}