#include "VectorMath.h"

float VerySmallAmount = 0.00001f;

namespace PlainPhysics
{
    Vector2D VectorMath::sfmlVector2DtoVector2D(sf::Vector2f vector) 
    {
        return Vector2D(vector.x, vector.y);
    }

    sf::Vector2f VectorMath::Vector2DtosfmlVector2D(Vector2D vector)
    {
        return sf::Vector2f(vector.x, vector.y);
    }

    bool VectorMath::NAN_Values(Vector2D vector)
    {
        return (std::isnan(vector.x) || std::isnan(vector.y));
    }

    Vector2D VectorMath::VectorTransformZ(Vector2D vector, Transform transform)
    {
        return Vector2D(transform.cos * vector.x - transform.sin * vector.y + transform.position.x, 
                        transform.sin * vector.x + transform.cos * vector.y + transform.position.y);
    }

    float VectorMath::Length(Vector2D vector)
    {
        return sqrt(vector.x * vector.x + vector.y * vector.y);
    }

    float VectorMath::LengthSquared(Vector2D vector)
    {
        return vector.x * vector.x + vector.y * vector.y;
    }

    float VectorMath::Distance(Vector2D a, Vector2D b) 
    {
        float dx = a.x - b.x;
        float dy = a.y - b.y;

        return sqrt(dx * dx + dy * dy);
    }

    float VectorMath::DistanceSquared(Vector2D a, Vector2D b)
    {
        float dx = a.x - b.x;
        float dy = a.y - b.y;

        return dx * dx + dy * dy;
    }

    Vector2D VectorMath::Normalize(Vector2D vector) 
    {
        float l = VectorMath::Length(vector);
        return Vector2D(vector.x / l, vector.y / l);
    }

    float VectorMath::DotProduct(Vector2D a, Vector2D b) 
    {
        return a.x * b.x + a.y * b.y;
    }

    float VectorMath::CrossProduct(Vector2D a, Vector2D b) 
    {
        return a.x * b.y - a.y * b.x;
    }

    bool VectorMath::NearlyEqual(float a, float b)
    {
        return std::abs(b - a) < VerySmallAmount;
    } 

    bool VectorMath::NearlyEqualVectors(Vector2D a, Vector2D b)
    {
        return DistanceSquared(a, b) < VerySmallAmount * VerySmallAmount;
    } 
}