#pragma once

namespace plain
{   
    namespace vectormath
    {
        float Length(Vector2D v);
        float Distance(Vector2D a, Vector2D b);
        Vector2D Normalize(Vector2D v);
        float DotProduct(Vector2D a, Vector2D b);
        float CrossProduct(Vector2D a, Vector2D b);

        Vector2D VectorTransformZ(Vector2D v, transform::Transform transform);

        Vector2D sfmlVector2DtoVector2D(sf::Vector2f v);
        sf::Vector2f Vector2DtosfmlVector2D(Vector2D v);

        // Plain::Vector3D sfmlVector3DtoVector3D(sf::Vector3f v);
        // sf::Vector3f Vector3DtosfmlVector3D(Plain::Vector3D v);
    }

}