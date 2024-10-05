#pragma once
#include <SFML/System/Vector2.hpp>
// #include <SFML/System/Vector3.hpp>


namespace PlainPhysics
{   
    namespace VectorMath
    {
        Vector2D sfmlVector2DtoVector2D(sf::Vector2f v);
        sf::Vector2f Vector2DtosfmlVector2D(Vector2D v);

        // Vector3D sfmlVector3DtoVector3D(sf::Vector3f v);
        // sf::Vector3f Vector3DtosfmlVector3D(Vector3D v);

        float Length(Vector2D v);
        float Distance(Vector2D a, Vector2D b);
        Vector2D Normalize(Vector2D v);
        float DotProduct(Vector2D a, Vector2D b);
        float CrossProduct(Vector2D a, Vector2D b);

        bool NAN_Values(Vector2D v);

        Vector2D VectorTransformZ(Vector2D v, Transform transform);
    }

}