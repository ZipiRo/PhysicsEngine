#pragma once

namespace Plain
{
    class Vector2D {
        public:
            float x, y;

            Vector2D();
            Vector2D(float x, float y);

            Vector2D &operator= (const Vector2D b);
            Vector2D operator+ (const Vector2D b) const;
            Vector2D operator- (const Vector2D b) const;
            Vector2D operator* (float scalar) const;
            Vector2D operator/ (float scalar) const;
            Vector2D &operator+= (const Vector2D& b);
            Vector2D &operator-= (const Vector2D& b);
            Vector2D &operator*= (float scalar);
            Vector2D &operator/= (float scalar);
            Vector2D Zero();
    };

    Vector2D multipyVector2D(const Vector2D a, const Vector2D b);
    Vector2D divideVector2D(const Vector2D a, const Vector2D b) ;
}