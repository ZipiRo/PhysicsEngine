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

    this->vertices = CreateBoxVertices(this->width, this->height);
    this->transformedVertices = this->vertices;

    this->rectangleShape = sf::RectangleShape(sf::Vector2f(width, height));
    this->rectangleShape.setOrigin(sf::Vector2f(width / 2, height / 2));
    this->rectangleShape.setFillColor(this->fillColor);
    this->rectangleShape.setOutlineColor(this->outlineColor);
    this->rectangleShape.setOutlineThickness(1);
    this->shape = &this->rectangleShape;

    this->UPDATETRANSFORM = true;
    this->UPDATEAABB = true;
}

void Plain::Rectangle::Draw(sf::RenderWindow& window)
{
    this->rectangleShape.setPosition(Vector2DtosfmlVector2D(this->position));
    this->rectangleShape.setRotation(this->angle);

    window.draw(this->rectangleShape);
}

Plain::LinkedList<Plain::Vector2D> Plain::CreateBoxVertices(float width, float heigth)
{
    float left = -width / 2.0f;
    float right = left + width;
    float bottom = -heigth / 2.0f;
    float top = bottom + heigth;

    Plain::LinkedList<Vector2D> vertices;
    vertices.insert(Vector2D(left, top));
    vertices.insert(Vector2D(right, top));
    vertices.insert(Vector2D(right, bottom));
    vertices.insert(Vector2D(left, bottom));

    return vertices;
}

Plain::LinkedList<Plain::Vector2D> Plain::Rectangle::GetTransformedVertices()
{
    if(this->UPDATETRANSFORM)
    {
        Plain::Transform transform(this->position, this->angle);

        for(int i = 0; i < this->vertices.length(); i++)
        {
            Plain::Vector2D v = this->vertices[i];
            this->transformedVertices[i] = Plain::VectorTransform(v,  transform);
        }

        this->UPDATETRANSFORM = false;
    }

    return this->transformedVertices;
}