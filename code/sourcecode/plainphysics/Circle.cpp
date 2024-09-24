#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <LinkedList.h>

#include "Vector2D.h"
#include "Transform.h"
#include "Vector.h"
#include "Body.h"
#include "Circle.h"

Plain::Circle::Circle(float radius, Vector2D position, float density, float restitution, sf::Color fillColor, sf::Color outlineColor, bool isStatic)
{
    this->position = position;
    this->linearVelocity = Vector2D().Zero();
    this->angle = 0.0f;
    this->angularVelocity = 0.0f;

    this->radius = radius;
    this->surface = this->radius * this->radius * 3.14159263f;
    this->density = density;
    this->mass = this->surface * this->density;
    this->restitution = restitution;

    this->fillColor = fillColor;
    this->outlineColor = outlineColor;

    this->isStatic = isStatic;

    this->type = CircleShape;

    this->circleShape = sf::CircleShape(this->radius);
    this->circleShape.setOrigin(sf::Vector2f(this->radius, this->radius));
    this->circleShape.setFillColor(this->fillColor);
    this->circleShape.setOutlineColor(this->outlineColor);
    this->circleShape.setOutlineThickness(1);

    this->shape = &this->circleShape;
}

void Plain::Circle::Draw(sf::RenderWindow& window)
{
    this->circleShape.setPosition(Vector2DtosfmlVector2D(this->position));
    this->circleShape.setRotation(this->angle);

    window.draw(this->circleShape);
}

Plain::Vector2D* Plain::Circle::GetTransformedVertices()
{
    return NULL;
}