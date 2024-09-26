#include <SFML/Graphics.hpp>
#include <list>

#include "Vector2D.h"
#include "Body.h"

plain::Body::Body () {}

void plain::Body::Move(plain::Vector2D amount) {
    this->position += amount;
    this->UPDATE_VERTICES = true;
}

void plain::Body::MoveTo(plain::Vector2D position) {
    this->position = position;
    this->UPDATE_VERTICES = true;
}

void plain::Body::Rotate(float amount) {
    this->angle += amount;
    this->UPDATE_VERTICES = true;
}

void plain::Body::RotateTo(float angle) {
    this->angle = angle;
    this->UPDATE_VERTICES = true;
}

void plain::Body::SetFillColor(sf::Color color) {
    this->fillColor = color;
    this->shape->setFillColor(this->fillColor);
}

void plain::Body::SetOutlineColor(sf::Color color) {
    this->outlineColor = color;
    this->shape->setOutlineColor(this->outlineColor);
}