#include <SFML/Graphics.hpp>
#include <Vector2D.hpp>

#include "Body.hpp"

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
}