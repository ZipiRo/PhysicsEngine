#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <Vector2D.hpp>

#include "Body.hpp"
#include "Circle.hpp"

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

    this->circle = sf::CircleShape(this->radius);
    this->circle.setOrigin(sf::Vector2f(this->radius, this->radius));
    this->circle.setFillColor(this->fillColor);
    this->circle.setOutlineColor(this->outlineColor);
    this->circle.setOutlineThickness(1);
}

void Plain::Circle::Draw(sf::RenderWindow& window)
{
    this->circle.setPosition(Vector2DtosfmlVector2D(this->position));
    this->circle.setRotation(this->angle);

    window.draw(this->circle);
}