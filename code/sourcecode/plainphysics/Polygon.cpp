#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Color.hpp>
#include <list>
#include <cmath>

#include "Vector2D.h"
#include "Transform.h"
#include "VectorMath.h"
#include "Body.h"
#include "Polygon.h"

namespace PlainPhysics 
{
    std::list<Vector2D> CreatePolygonVertices(int sides, float radius)
    {
        std::list<Vector2D> vertices;

        for(int i = 0; i < sides; i++)
        {
            float e = 2 * i * 3.141592f;
            float vertexX = cosf((e + 1) / float(sides)) * radius; 
            float vertexY = sinf((e + 1) / float(sides)) * radius;

            vertexX *= 1.0f;
            vertexY *= 1.0f;

            vertices.push_back(Vector2D(vertexX, vertexY));
        }

        return vertices;
    }
    
    std::list<Vector2D> UpdatePolygonVertices(std::list<Vector2D> vertices, Vector2D position, float angle)
    {
        std::list<Vector2D> transformVertices;

        Transform transform(position, angle);

        for(Vector2D v : vertices)
            transformVertices.push_back(VectorMath::VectorTransformZ(v, transform));

        return transformVertices;
    }

    Polygon::Polygon (int sides, float radius, Vector2D position, float density, float restitution, sf::Color fillColor, sf::Color outlineColor, bool isStatic)
    {
        this->position = position;
        this->linearVelocity = Vector2D(0, 0);
        this->angle = 0.0f;
        this->angularVelocity = 0.0f;

        this->force = Vector2D(0, 0);

        this->radius = radius;
        this->surface = sides * (radius * radius) * sinf(2 * 3.141592f / sides) / 2;

        this->density = density;
        this->mass = isStatic ? 1000000.0f : this->surface * this->density;
        this->invMass = 1.0f / mass;
        this->restitution = restitution;

        this->fillColor = fillColor;
        this->outlineColor = outlineColor;

        this->isStatic = isStatic;

        this->shapeType = Body::PolygonShape;

        this->vertices = CreatePolygonVertices(sides, radius);
        this->transformVertices = this->vertices;

        this->polygonShape = sf::ConvexShape(sides);

        int index = 0;
        for(Vector2D vertex : vertices)
            this->polygonShape.setPoint(index++, VectorMath::Vector2DtosfmlVector2D(vertex));

        this->polygonShape.setFillColor(this->fillColor);
        this->polygonShape.setOutlineColor(this->outlineColor);
        this->polygonShape.setOutlineThickness(1);
        this->shape = &this->polygonShape;

        this->UPDATE_VERTICES = true;
        this->UPDATE_AABB = true;
    }

    void Polygon::Draw(sf::RenderWindow& window)
    {   
        if(this->UPDATE_VERTICES)
            this->transformVertices = UpdatePolygonVertices(this->vertices, this->position, this->angle);

        this->polygonShape.setPosition(VectorMath::Vector2DtosfmlVector2D(this->position));
        this->polygonShape.setRotation(this->angle);

        window.draw(this->polygonShape);

        this->UPDATE_VERTICES = false;
    }

    std::list<Vector2D> Polygon::GetTransformedVertices()
    {
        if(this->UPDATE_VERTICES)
            this->transformVertices = UpdatePolygonVertices(this->vertices, this->position, this->angle);

        this->UPDATE_VERTICES = false;
        return this->transformVertices;
    }   
}