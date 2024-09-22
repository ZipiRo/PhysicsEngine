#pragma once

namespace Plain
{
    class Vector2D {
        public:
            float x, y;

            Vector2D();
            Vector2D(float x, float y);

            Vector2D operator= (Vector2D b);
            Vector2D operator+ (Vector2D b);
            Vector2D operator- (Vector2D b);
            Vector2D operator+= (Vector2D b);
            Vector2D operator-= (Vector2D b);
            Vector2D operator* (float scalar);
            Vector2D operator/ (float scalar);
            Vector2D operator*= (float scalar);
            Vector2D operator/= (float scalar);
            Vector2D Zero();
    };

    Vector2D multipyVector2D(Vector2D a, Vector2D b);
    Vector2D divideVector2D(Vector2D a, Vector2D b) ;
}