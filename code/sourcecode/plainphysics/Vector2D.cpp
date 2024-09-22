#include "Vector2D.h"

Plain::Vector2D::Vector2D() {
    this->x = 0;
    this->y = 0;
}

Plain::Vector2D::Vector2D(float x, float y) {
    this->x = x;
    this->y = y;
}

Plain::Vector2D Plain::Vector2D::operator= (Plain::Vector2D b) {
    this->x = b.x;
    this->y = b.y;
    return *this;
}

Plain::Vector2D Plain::Vector2D::operator+ (Plain::Vector2D b) {
    return Vector2D(this->x + b.x, this->y + b.y);
}

Plain::Vector2D Plain::Vector2D::operator- (Plain::Vector2D b) {
    return Vector2D(this->x - b.x, this->y - b.y);
}

Plain::Vector2D Plain::Vector2D::operator+= (Plain::Vector2D b) {
    this->x += b.x;
    this->y += b.y;
    return *this;
}

Plain::Vector2D Plain::Vector2D::operator-= (Plain::Vector2D b) {
    this->x -= b.x;
    this->y -= b.y;
    return *this;
}

Plain::Vector2D Plain::Vector2D::operator* (float scalar) {
    return Vector2D(this->x * scalar, this->y * scalar);
}

Plain::Vector2D Plain::Vector2D::operator/ (float scalar) {
    return Vector2D(this->x / scalar, this->y / scalar);
}

Plain::Vector2D Plain::Vector2D::operator*= (float scalar) {
    this->x *= scalar;
    this->y *= scalar;
    return *this;
}

Plain::Vector2D Plain::Vector2D::operator/= (float scalar) {
    this->x /= scalar;
    this->y /= scalar;
    return *this;
}

Plain::Vector2D Plain::Vector2D::Zero () {
    return Vector2D(0, 0);
}

Plain::Vector2D Plain::multipyVector2D(Plain::Vector2D a, Plain::Vector2D b) {
    return Plain::Vector2D(a.x * b.x, a.y * b.y);
}

Plain::Vector2D Plain::divideVector2D(Plain::Vector2D a, Plain::Vector2D b) {
    return Plain::Vector2D(a.x / b.x, a.y / b.y);
}