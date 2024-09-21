#include <SFML/Graphics.hpp>
#include <Vector2D.h>

#include "Body.h"

namespace Plain{
    Body::Body () {}

    void Body::Move(Vector2D amount){
		    this->position += amount;
    }

    void Body::MoveTo(Vector2D position){
		    this->position = position;
    }

    void Body::Rotate(float amount){
        this->angle += amount;
    }

    void Body::RotateTo(float angle){
		    this->angle = angle;
    }

    void Body::SetFillColor(sf::Color color){
        this->fillColor = color;
        this->shape->setFillColor(this->fillColor);
    }

    void Body::SetOutlineColor(sf::Color color){
        this->outlineColor = color;
        this->shape->setOutlineColor(this->outlineColor);
    }
}