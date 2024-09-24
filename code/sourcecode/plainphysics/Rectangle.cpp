#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Color.hpp>
#include <LinkedList.h>

#include "Vector2D.h"
#include "Transform.h"
#include "Vector.h"
#include "Body.h"
#include "Rectangle.h"

Plain::Rectangle::Rectangle (float width, float height, Vector2D position, float density, float restitution, sf::Color fillColor, sf::Color outlineColor, bool isStatic)
{
    this->position = position;
    this->linearVelocity = Vector2D().Zero();
    this->angle = 0.0f;
    this->angularVelocity = 0.0f;

    this->width = width;
    this->height = height;
    this->surface = this->width * this->height;
    this->density = density;
    this->mass = this->surface * this->density;
    this->restitution = restitution;

    this->fillColor = fillColor;
    this->outlineColor = outlineColor;

    this->isStatic = isStatic;

    this->type = RectangleShape;

    for(int i = 0; i < 4; i++)
    {
        this->vertices[i] = CreateRectangleVertices(this->width, this->height)[i];
        this->transformVertices[i] = vertices[i];
    }

    this->rectangleShape = sf::RectangleShape(sf::Vector2f(width, height));
    this->rectangleShape.setOrigin(sf::Vector2f(width / 2, height / 2));
    this->rectangleShape.setFillColor(this->fillColor);
    this->rectangleShape.setOutlineColor(this->outlineColor);
    this->rectangleShape.setOutlineThickness(1);
    this->shape = &this->rectangleShape;

    this->UPDATE_VERTICES = true;
    this->UPDATE_AABB = true;
}

void Plain::Rectangle::Draw(sf::RenderWindow& window)
{   
    this->GetTransformedVertices();

    this->rectangleShape.setPosition(Vector2DtosfmlVector2D(this->position));
    this->rectangleShape.setRotation(this->angle);

    window.draw(this->rectangleShape);

    this->UPDATE_VERTICES = false;
}

Plain::Vector2D* Plain::CreateRectangleVertices(float width, float heigth)
{
    float left = -width / 2.0f;
    float right = left + width;
    float bottom = -heigth / 2.0f;
    float top = bottom + heigth;

    Vector2D vertices[4];
    Vector2D *s_Vector2Dp = vertices;

    vertices[0] = Vector2D(left, top);
    vertices[1] = Vector2D(right, top);
    vertices[2] = Vector2D(right, bottom);
    vertices[3] = Vector2D(left, bottom);

    return s_Vector2Dp;
}

Plain::Vector2D* Plain::TransformVertices(Plain::Vector2D* vertices, Plain::Vector2D position, float angle)
{
    Transform transform(position, angle);
    
    Vector2D transformVertices[4];
    Vector2D *s_Vector2Dp = transformVertices;

    for(int i = 0; i < 4; i++)
    {
        Vector2D v = vertices[i];
        transformVertices[i] = VectorTransform(v, transform);
    }

    return s_Vector2Dp;
}

Plain::Vector2D* Plain::Rectangle::GetTransformedVertices()
{
    if(this->UPDATE_VERTICES)
    {
        for(int i = 0; i < 4; i++)
            this->transformVertices[i] = TransformVertices(this->vertices, this->position, this->angle)[i];
    }

    this->UPDATE_VERTICES = false;
    return this->transformVertices;
}