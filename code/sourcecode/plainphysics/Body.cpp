#include "Body.h"

namespace PlainPhysics
{
    Body::Body () {}

    void Body::Move(Vector2D amount) {
        this->position += amount;
        this->UPDATE_VERTICES = true;
        this->UPDATE_AABB = true;
    }

    void Body::MoveTo(Vector2D position) {
        this->position = position;
        this->UPDATE_VERTICES = true;
        this->UPDATE_AABB = true;
    }

    void Body::Rotate(float amount) {
        this->angle += amount;
        this->UPDATE_VERTICES = true;
        this->UPDATE_AABB = true;
    }

    void Body::RotateTo(float angle) {
        this->angle = angle;
        this->UPDATE_VERTICES = true;
        this->UPDATE_AABB = true;
    }

    void Body::AddForce(Vector2D amount) {
        this->force = amount;
    }

    void Body::SetFillColor(sf::Color color) {
        this->fillColor = color;
        this->shape->setFillColor(this->fillColor);
    }

    void Body::SetOutlineColor(sf::Color color) {
        this->outlineColor = color;
        this->shape->setOutlineColor(this->outlineColor);
    }

    void Body::Step(float delta, int totalIterations) {
        if(this->isStatic) return;
        
        delta /= float(totalIterations);

        Vector2D acceleration = this->force / this->mass;

        this->linearVelocity += acceleration * delta;
        this->position += this->linearVelocity * delta;

        this->angle += this->angularVelocity * (180 / 3.141592f) * delta;
        
        this->force = Vector2D(0, 0);

        this->UPDATE_VERTICES = true;
        this->UPDATE_AABB = true;
    }
}
