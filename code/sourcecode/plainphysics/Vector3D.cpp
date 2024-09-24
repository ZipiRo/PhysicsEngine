#include "Vector3D.h"

plain::Vector3D::Vector3D() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

plain::Vector3D::Vector3D(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

plain::Vector3D plain::Vector3D::operator= (Vector3D b) {
    this->x = b.x;
    this->y = b.y;
    this->z = b.z;
    return *this;
}

plain::Vector3D plain::Vector3D::operator+ (Vector3D b) {
    return Vector3D(this->x + b.x, this->y + b.y, this->z + b.z);
}

plain::Vector3D plain::Vector3D::operator- (Vector3D b) {
    return Vector3D(this->x - b.x, this->y - b.y, this->z - b.z);
}

plain::Vector3D plain::Vector3D::operator+= (Vector3D b) {
    this->x += b.x;
    this->y += b.y;
    this->z += b.z;
    return *this;
}

plain::Vector3D plain::Vector3D::operator-= (Vector3D b) {
    this->x -= b.x;
    this->y -= b.y;
    this->z -= b.z;
    return *this;
}

plain::Vector3D plain::Vector3D::operator* (float scalar) {
    return Vector3D(this->x * scalar, this->y * scalar, this->z + scalar);
}

plain::Vector3D plain::Vector3D::operator/ (float scalar) {
    return Vector3D(this->x / scalar, this->y / scalar, this->z / scalar);
}

plain::Vector3D plain::Vector3D::operator*= (float scalar) {
    this->x *= scalar;
    this->y *= scalar;
    this->z *= scalar;
    return *this;
}

plain::Vector3D plain::Vector3D::operator/= (float scalar) {
    this->x /= scalar;
    this->y /= scalar;
    this->z /= scalar;
    return *this;
}

plain::Vector3D plain::multipyVector3D(plain::Vector3D a, plain::Vector3D b) {
    return plain::Vector3D(a.x * b.x, a.y * b.y, a.z + b.z);
}

plain::Vector3D plain::divideVector3D(plain::Vector3D a, plain::Vector3D b) {
    return plain::Vector3D(a.x / b.x, a.y / b.y, a.z / b.z);
}