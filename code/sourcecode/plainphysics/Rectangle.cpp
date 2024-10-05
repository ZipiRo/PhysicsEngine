#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Color.hpp>
#include <list>

#include "Vector2D.h"
#include "Transform.h"
#include "VectorMath.h"
#include "Body.h"
#include "Rectangle.h"

namespace PlainPhysics 
{
    std::list<Vector2D> CreateRectangleVertices(float width, float height)
    {
        std::list<Vector2D> vertices;

        float left = -width / 2.0f;
        float right = left + width;
        float bottom = -height / 2.0f;
        float top = bottom + height;

        vertices.push_back(Vector2D(left, top));
        vertices.push_back(Vector2D(right, top));
        vertices.push_back(Vector2D(right, bottom));
        vertices.push_back(Vector2D(left, bottom));

        return vertices;
    }
    
    std::list<Vector2D> UpdateRectangleVertices(std::list<Vector2D> vertices, Vector2D position, float angle)
    {
        std::list<Vector2D> transformVertices;

        Transform transform(position, angle);

        for(Vector2D v : vertices)
            transformVertices.push_back(VectorMath::VectorTransformZ(v, transform));

        return transformVertices;
    }

    Rectangle::Rectangle (float width, float height, Vector2D position, float density, float restitution, sf::Color fillColor, sf::Color outlineColor, bool isStatic)
    {
        this->position = position;
        this->linearVelocity = Vector2D(0, 0);
        this->angle = 0.0f;
        this->angularVelocity = 0.0f;

        this->force = Vector2D(0, 0);

        this->width = width;
        this->height = height;
        this->surface = this->width * this->height;
        this->density = density;
        this->mass = isStatic ? 1000000.0f : this->surface * this->density;
        this->invMass = 1.0f / mass;
        this->restitution = restitution;

        this->fillColor = fillColor;
        this->outlineColor = outlineColor;

        this->isStatic = isStatic;

        this->shapeType = RectangleShape;

        this->vertices = CreateRectangleVertices(this->width, this->height);
        this->transformVertices = this->vertices;

        this->rectangleShape = sf::RectangleShape(sf::Vector2f(width, height));
        this->rectangleShape.setOrigin(sf::Vector2f(this->width / 2, this->height / 2));
        this->rectangleShape.setFillColor(this->fillColor);
        this->rectangleShape.setOutlineColor(this->outlineColor);
        this->rectangleShape.setOutlineThickness(1);
        this->shape = &this->rectangleShape;

        this->UPDATE_VERTICES = true;
        this->UPDATE_AABB = true;
    }

    void Rectangle::Draw(sf::RenderWindow& window)
    {   
        if(this->UPDATE_VERTICES)
            this->transformVertices = UpdateRectangleVertices(this->vertices, this->position, this->angle);

        this->rectangleShape.setPosition(VectorMath::Vector2DtosfmlVector2D(this->position));
        this->rectangleShape.setRotation(this->angle);

        window.draw(this->rectangleShape);

        this->UPDATE_VERTICES = false;
    }

    std::list<Vector2D> Rectangle::GetTransformedVertices()
    {
        if(this->UPDATE_VERTICES)
            this->transformVertices = UpdateRectangleVertices(this->vertices, this->position, this->angle);

        this->UPDATE_VERTICES = false;
        return this->transformVertices;
    }   
}