#pragma once
#include <SFML/System/Vector2.hpp>
#include <cmath>

#include "Vector2D.h"
#include "Transform.h"

namespace PlainPhysics
{   
    namespace VectorMath
    {
        Vector2D sfmlVector2DtoVector2D(sf::Vector2f v);
        sf::Vector2f Vector2DtosfmlVector2D(Vector2D v);

        float Length(Vector2D v);
        float Distance(Vector2D a, Vector2D b);
        Vector2D Normalize(Vector2D v);
        float DotProduct(Vector2D a, Vector2D b);
        float CrossProduct(Vector2D a, Vector2D b);

        bool NAN_Values(Vector2D v);

        Vector2D VectorTransformZ(Vector2D v, Transform transform);
    }

}