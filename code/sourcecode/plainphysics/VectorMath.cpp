#include <SFML/System/Vector2.hpp>
// #include <SFML/System/Vector3.hpp>
#include <cmath>

#include "Vector2D.h"
// #include "Vector3D.h"
#include "Transform.h"
#include "VectorMath.h"

namespace plain
{
    Vector2D vectormath::sfmlVector2DtoVector2D(sf::Vector2f v) {
        return plain::Vector2D(v.x, v.y);
    }

    sf::Vector2f vectormath::Vector2DtosfmlVector2D(plain::Vector2D v) {
        return sf::Vector2f(v.x, v.y);
    }

    // Plain::Vector3D Plain::sfmlVector3DtoVector3D(sf::Vector3f v) {
    //     return Plain::Vector3D(v.x, v.y, v.z);
    // }

    // sf::Vector3f Plain::Vector3DtosfmlVector3D(Plain::Vector3D v) {
    //     return sf::Vector3f(v.x, v.y, v.z);
    // }

    bool vectormath::NAN_Values(Vector2D v) {
        return (std::isnan(v.x) && std::isnan(v.y));
    }

    plain::Vector2D vectormath::VectorTransformZ(plain::Vector2D v, transform::Transform transform) {
        return plain::Vector2D(transform.cos * v.x - transform.sin * v.y + transform.position.x, 
                                transform.sin * v.x + transform.cos * v.y + transform.position.y);
    }

    float vectormath::Length(plain::Vector2D v) {
        return sqrt(v.x * v.x + v.y * v.y);
    }

    float vectormath::Distance(plain::Vector2D a, plain::Vector2D b) {
        float dx = a.x - b.x;
        float dy = a.y - b.y;

        return sqrt(dx * dx + dy * dy);
    }

    plain::Vector2D vectormath::Normalize(plain::Vector2D v) {
        float len = vectormath::Length(v);
        return plain::Vector2D(v.x / len, v.y / len);
    }

    float vectormath::DotProduct(plain::Vector2D a, plain::Vector2D b) {
        return a.x * b.x + a.y * b.y;
    }

    float vectormath::CrossProduct(plain::Vector2D a, plain::Vector2D b) {
        return a.x * b.y - a.y * b.x;
    }
}