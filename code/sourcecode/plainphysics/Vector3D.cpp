#include "Vector3D.h"

PlainPhysics::Vector3D::Vector3D() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

PlainPhysics::Vector3D::Vector3D(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

PlainPhysics::Vector3D PlainPhysics::Vector3D::operator= (Vector3D b) {
    this->x = b.x;
    this->y = b.y;
    this->z = b.z;
    return *this;
}

PlainPhysics::Vector3D PlainPhysics::Vector3D::operator+ (Vector3D b) {
    return Vector3D(this->x + b.x, this->y + b.y, this->z + b.z);
}

PlainPhysics::Vector3D PlainPhysics::Vector3D::operator- (Vector3D b) {
    return Vector3D(this->x - b.x, this->y - b.y, this->z - b.z);
}

PlainPhysics::Vector3D PlainPhysics::Vector3D::operator+= (Vector3D b) {
    this->x += b.x;
    this->y += b.y;
    this->z += b.z;
    return *this;
}

PlainPhysics::Vector3D PlainPhysics::Vector3D::operator-= (Vector3D b) {
    this->x -= b.x;
    this->y -= b.y;
    this->z -= b.z;
    return *this;
}

PlainPhysics::Vector3D PlainPhysics::Vector3D::operator* (float scalar) {
    return Vector3D(this->x * scalar, this->y * scalar, this->z + scalar);
}

PlainPhysics::Vector3D PlainPhysics::Vector3D::operator/ (float scalar) {
    return Vector3D(this->x / scalar, this->y / scalar, this->z / scalar);
}

PlainPhysics::Vector3D PlainPhysics::Vector3D::operator*= (float scalar) {
    this->x *= scalar;
    this->y *= scalar;
    this->z *= scalar;
    return *this;
}

PlainPhysics::Vector3D PlainPhysics::Vector3D::operator/= (float scalar) {
    this->x /= scalar;
    this->y /= scalar;
    this->z /= scalar;
    return *this;
}

PlainPhysics::Vector3D PlainPhysics::multipyVector3D(PlainPhysics::Vector3D a, PlainPhysics::Vector3D b) {
    return PlainPhysics::Vector3D(a.x * b.x, a.y * b.y, a.z + b.z);
}

PlainPhysics::Vector3D PlainPhysics::divideVector3D(PlainPhysics::Vector3D a, PlainPhysics::Vector3D b) {
    return PlainPhysics::Vector3D(a.x / b.x, a.y / b.y, a.z / b.z);
}