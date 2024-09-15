#include <SFML/Graphics.hpp>
#include <Vector2D.hpp>

#include "Body.hpp"

namespace Plain{
    Body::Body () {}

    void Body::Move(Vector2D amount){
		this->position += amount;
    }
}