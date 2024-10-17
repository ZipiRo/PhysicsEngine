#pragma once
#include <SFML/System/Vector2.hpp>
#include <cmath>

#include "Vector2D.h"
#include "Transform.h"

namespace PlainPhysics
{   
    namespace VectorMath
    {
        Vector2D sfmlVector2DtoVector2D(sf::Vector2f vector);
        sf::Vector2f Vector2DtosfmlVector2D(Vector2D vector);

        float Length(Vector2D vector);
        float LengthSquared(Vector2D vector);
        float Distance(Vector2D a, Vector2D b);
        float DistanceSquared(Vector2D a, Vector2D b);
        Vector2D Normalize(Vector2D vector);
        float DotProduct(Vector2D a, Vector2D b);
        float CrossProduct(Vector2D a, Vector2D b);
        bool NearlyEqual(float a, float b); /// Get this out !!! make another class
        bool NearlyEqualVectors(Vector2D a, Vector2D b);

        bool NAN_Values(Vector2D vector);

        Vector2D VectorTransformZ(Vector2D vector, Transform transform);
    }
}