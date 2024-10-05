#include <SFML/System/Vector2.hpp>
// #include <SFML/System/Vector3.hpp>
#include <cmath>

#include "Vector2D.h"
// #include "Vector3D.h"
#include "Transform.h"
#include "VectorMath.h"

namespace PlainPhysics
{
    Vector2D VectorMath::sfmlVector2DtoVector2D(sf::Vector2f v) {
        return Vector2D(v.x, v.y);
    }

    sf::Vector2f VectorMath::Vector2DtosfmlVector2D(Vector2D v) {
        return sf::Vector2f(v.x, v.y);
    }

    // Vector3D VectorMath::sfmlVector3DtoVector3D(sf::Vector3f v) {
    //     return Vector3D(v.x, v.y, v.z);
    // }

    // sf::Vector3f VectorMath::Vector3DtosfmlVector3D(Vector3D v) {
    //     return sf::Vector3f(v.x, v.y, v.z);
    // }

    bool VectorMath::NAN_Values(Vector2D v) {
        return (std::isnan(v.x) || std::isnan(v.y));
    }

    Vector2D VectorMath::VectorTransformZ(Vector2D v, Transform transform) {
        return Vector2D(transform.cos * v.x - transform.sin * v.y + transform.position.x, 
                        transform.sin * v.x + transform.cos * v.y + transform.position.y);
    }

    float VectorMath::Length(Vector2D v) {
        return sqrt(v.x * v.x + v.y * v.y);
    }

    float VectorMath::Distance(Vector2D a, Vector2D b) {
        float dx = a.x - b.x;
        float dy = a.y - b.y;

        return sqrt(dx * dx + dy * dy);
    }

    Vector2D VectorMath::Normalize(Vector2D v) {
        float l = VectorMath::Length(v);
        return Vector2D(v.x / l, v.y / l);
    }

    float VectorMath::DotProduct(Vector2D a, Vector2D b) {
        return a.x * b.x + a.y * b.y;
    }

    float VectorMath::CrossProduct(Vector2D a, Vector2D b) {
        return a.x * b.y - a.y * b.x;
    }
}