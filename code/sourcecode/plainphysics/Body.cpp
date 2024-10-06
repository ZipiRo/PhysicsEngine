#include <SFML/Graphics.hpp>
#include <list>

#include "Vector2D.h"
#include "AABB.h"
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

    void Body::SetStatic(bool isStatic) {
        this->isStatic = isStatic;

        if(!isStatic) 
        {
            this->mass = this->surface * this->density;
        }
        else 
        {
            this->mass = 1000000.0f;
        }

        this->invMass = 1.0f / this->mass;
    }

    void Body::Step(float delta, int totalItterations) {
        if(this->isStatic) return;
        
        delta /= float(totalItterations);

        Vector2D acceleration = this->force / this->mass;

        this->linearVelocity += acceleration * delta;
        this->position += this->linearVelocity * delta;

        this->angle += this->angularVelocity * delta;
        
        this->force = Vector2D(0, 0);

        this->UPDATE_VERTICES = true;
        this->UPDATE_AABB = true;
    }
}
