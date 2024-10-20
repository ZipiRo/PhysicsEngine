#include "Vector2D.h"

namespace PlainPhysics
{
    Vector2D::Vector2D() {
        this->x = 0;
        this->y = 0;
    }

    Vector2D::Vector2D(float x, float y) {
        this->x = x;
        this->y = y;
    }

    Vector2D& Vector2D::operator= (const Vector2D b) {
        if (this != &b) {
            this->x = b.x;
            this->y = b.y;
        }
        return *this;
    }

    Vector2D Vector2D::operator-() const {
        return Vector2D(-this->x, -this->y);
    }

    Vector2D Vector2D::operator+ (const Vector2D b) const {
        return Vector2D(this->x + b.x, this->y + b.y);
    }

    Vector2D Vector2D::operator- (const Vector2D b) const {
        return Vector2D(this->x - b.x, this->y - b.y);
    }

    Vector2D operator* (float scalar, const Vector2D& a) {
        return Vector2D(scalar * a.x, scalar * a.y);
    }

    Vector2D operator/ (float scalar, const Vector2D& a) {
        return Vector2D(scalar / a.x, scalar / a.y);
    }

    Vector2D Vector2D::operator* (float scalar) const {
        return Vector2D(this->x * scalar, this->y * scalar);
    }
    
    Vector2D Vector2D::operator/ (float scalar) const {
        return Vector2D(this->x / scalar, this->y / scalar);
    }

    Vector2D& Vector2D::operator+= (const Vector2D& b) {
        this->x += b.x;
        this->y += b.y;
        return *this;
    }

    Vector2D& Vector2D::operator-= (const Vector2D& b) {
        this->x -= b.x;
        this->y -= b.y;
        return *this;
    }

    Vector2D& Vector2D::operator*= (float scalar) {
        this->x *= scalar;
        this->y *= scalar;
        return *this;
    }

    Vector2D& Vector2D::operator/= (float scalar) {
        this->x /= scalar;
        this->y /= scalar;
        return *this;
    }

    Vector2D multipyVector2D(const Vector2D a, const Vector2D b) {
        return Vector2D(a.x * b.x, a.y * b.y);
    }

    Vector2D divideVector2D(const Vector2D a, const Vector2D b) {
        return Vector2D(a.x / b.x, a.y / b.y);
    }
}