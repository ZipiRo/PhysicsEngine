#include <SFML/System/Vector2.hpp>
// #include <SFML/System/Vector3.hpp>
#include <cmath>

#include "Vector2D.h"
// #include "Vector3D.h"
#include "Transform.h"
#include "VectorMath.h"

namespace PlainPhysics
{
    Vector2D vectormath::sfmlVector2DtoVector2D(sf::Vector2f v) {
        return PlainPhysics::Vector2D(v.x, v.y);
    }

    sf::Vector2f vectormath::Vector2DtosfmlVector2D(PlainPhysics::Vector2D v) {
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

    PlainPhysics::Vector2D vectormath::VectorTransformZ(PlainPhysics::Vector2D v, transform::Transform transform) {
        return PlainPhysics::Vector2D((transform.cos * v.x - transform.sin * v.y) + transform.position.x, 
                                (transform.sin * v.x + transform.cos * v.y) + transform.position.y);
    }

    float vectormath::Length(PlainPhysics::Vector2D v) {
        return sqrt(v.x * v.x + v.y * v.y);
    }

    float vectormath::Distance(PlainPhysics::Vector2D a, PlainPhysics::Vector2D b) {
        float dx = a.x - b.x;
        float dy = a.y - b.y;

        return sqrt(dx * dx + dy * dy);
    }

    PlainPhysics::Vector2D vectormath::Normalize(PlainPhysics::Vector2D v) {
        float l = vectormath::Length(v);
        return PlainPhysics::Vector2D(v.x / l, v.y / l);
    }

    float vectormath::DotProduct(PlainPhysics::Vector2D a, PlainPhysics::Vector2D b) {
        return a.x * b.x + a.y * b.y;
    }

    float vectormath::CrossProduct(PlainPhysics::Vector2D a, PlainPhysics::Vector2D b) {
        return a.x * b.y - a.y * b.x;
    }
}