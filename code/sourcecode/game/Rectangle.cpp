#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <Vector2D.hpp>
#include "Body.hpp"

#include "Rectangle.hpp"

namespace Plain{
    Rectangle::Rectangle (float width, float height, Vector2D position, float density, float restitution, sf::Color fillColor, sf::Color outlineColor, bool isStatic)
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
    }

    void Rectangle::Draw(sf::RenderWindow& window)
    {
        this->rectangle.setPosition(Vector2DtosfmlVector2D(this->position));
        this->rectangle.setRotation(this->angle);
        this->rectangle.setFillColor(this->fillColor);
        this->rectangle.setOutlineColor(this->outlineColor);
        this->rectangle.setOutlineThickness(1);

        window.draw(this->rectangle);
    }
}