#include "Vector3D.h"

Plain::Vector3D::Vector3D() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Plain::Vector3D::Vector3D(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Plain::Vector3D Plain::Vector3D::operator= (Vector3D b) {
    this->x = b.x;
    this->y = b.y;
    this->z = b.z;
    return *this;
}

Plain::Vector3D Plain::Vector3D::operator+ (Vector3D b) {
    return Vector3D(this->x + b.x, this->y + b.y, this->z + b.z);
}

Plain::Vector3D Plain::Vector3D::operator- (Vector3D b) {
    return Vector3D(this->x - b.x, this->y - b.y, this->z - b.z);
}

Plain::Vector3D Plain::Vector3D::operator+= (Vector3D b) {
    this->x += b.x;
    this->y += b.y;
    this->z += b.z;
    return *this;
}

Plain::Vector3D Plain::Vector3D::operator-= (Vector3D b) {
    this->x -= b.x;
    this->y -= b.y;
    this->z -= b.z;
    return *this;
}

Plain::Vector3D Plain::Vector3D::operator* (float scalar) {
    return Vector3D(this->x * scalar, this->y * scalar, this->z + scalar);
}

Plain::Vector3D Plain::Vector3D::operator/ (float scalar) {
    return Vector3D(this->x / scalar, this->y / scalar, this->z / scalar);
}

Plain::Vector3D Plain::Vector3D::operator*= (float scalar) {
    this->x *= scalar;
    this->y *= scalar;
    this->z *= scalar;
    return *this;
}

Plain::Vector3D Plain::Vector3D::operator/= (float scalar) {
    this->x /= scalar;
    this->y /= scalar;
    this->z /= scalar;
    return *this;
}

Plain::Vector3D multipyVector3D(Plain::Vector3D a, Plain::Vector3D b) {
    return Plain::Vector3D(a.x * b.x, a.y * b.y, a.z + b.z);
}

Plain::Vector3D divideVector3D(Plain::Vector3D a, Plain::Vector3D b) {
    return Plain::Vector3D(a.x / b.x, a.y / b.y, a.z / b.z);
}