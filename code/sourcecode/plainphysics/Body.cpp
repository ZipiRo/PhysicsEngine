#include <SFML/Graphics.hpp>

#include "Vector2D.h"
#include "Body.h"

Plain::Body::Body () {}

void Plain::Body::Move(Plain::Vector2D amount) {
    this->position += amount;
    this->UPDATETRANSFORM = true;
}

void Plain::Body::MoveTo(Plain::Vector2D position) {
    this->position = position;
    this->UPDATETRANSFORM = true;
}

void Plain::Body::Rotate(float amount) {
    this->angle += amount;
    this->UPDATETRANSFORM = true;
}

void Plain::Body::RotateTo(float angle) {
    this->angle = angle;
    this->UPDATETRANSFORM = true;
}

void Plain::Body::SetFillColor(sf::Color color) {
    this->fillColor = color;
    this->shape->setFillColor(this->fillColor);
}

void Plain::Body::SetOutlineColor(sf::Color color) {
    this->outlineColor = color;
    this->shape->setOutlineColor(this->outlineColor);
}