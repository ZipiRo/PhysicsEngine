#include <SFML/Graphics.hpp>
#include <list>

#include "Vector2D.h"
#include "Body.h"

namespace PlainPhysics
{
    Body::Body () {}

    void Body::Move(Vector2D amount) {
        this->position += amount;
        this->UPDATE_VERTICES = true;
    }

    void Body::MoveTo(Vector2D position) {
        this->position = position;
        this->UPDATE_VERTICES = true;
    }

    void Body::Rotate(float amount) {
        this->angle += amount;
        this->UPDATE_VERTICES = true;
    }

    void Body::RotateTo(float angle) {
        this->angle = angle;
        this->UPDATE_VERTICES = true;
    }

    void Body::SetFillColor(sf::Color color) {
        this->fillColor = color;
        this->shape->setFillColor(this->fillColor);
    }

    void Body::SetOutlineColor(sf::Color color) {
        this->outlineColor = color;
        this->shape->setOutlineColor(this->outlineColor);
    }

    void Body::Step(float delta) {
        this->position += this->linearVelocity * delta;
        this->angle += this->angularVelocity * delta;
        
        this->UPDATE_VERTICES = true;
    }
}
