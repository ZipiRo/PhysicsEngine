#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <cmath>

#include "Vector2D.h"
// #include "Vector3D.h"
#include "Transform.h"
#include "Vector.h"

Plain::Vector2D Plain::sfmlVector2DtoVector2D(sf::Vector2f v) {
    return Plain::Vector2D(v.x, v.y);
}

sf::Vector2f Plain::Vector2DtosfmlVector2D(Plain::Vector2D v) {
    return sf::Vector2f(v.x, v.y);
}

// Plain::Vector3D Plain::sfmlVector3DtoVector3D(sf::Vector3f v) {
//     return Plain::Vector3D(v.x, v.y, v.z);
// }

// sf::Vector3f Plain::Vector3DtosfmlVector3D(Plain::Vector3D v) {
//     return sf::Vector3f(v.x, v.y, v.z);
// }

Plain::Vector2D Plain::VectorTransform(Plain::Vector2D v, Plain::Transform transform) {
    return Plain::Vector2D(transform.cos * v.x - transform.sin * v.y+ transform.position.x, 
                            transform.sin * v.x + transform.cos * v.y+ transform.position.y);
}

float Plain::Length(Plain::Vector2D v) {
    return sqrt(v.x * v.x + v.y * v.y);
}

float Plain::Distance(Plain::Vector2D a, Plain::Vector2D b) {
    float dx = a.x - b.x;
    float dy = a.y - b.y;

    return sqrt(dx * dx + dy * dy);
}

Plain::Vector2D Plain::Normalize(Plain::Vector2D v) {
    float len = Plain::Length(v);
    return Plain::Vector2D(v.x / len, v.y / len);
}

float Plain::DotProduct(Plain::Vector2D a, Plain::Vector2D b) {
    return a.x * b.x + a.y * b.y;
}

float Plain::CrossProduct(Plain::Vector2D a, Plain::Vector2D b) {
    return a.x * b.y - a.y * b.x;
}