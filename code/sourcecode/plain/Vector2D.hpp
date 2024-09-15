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

    Plain::Vector2D sfmlVector2DtoVector2D(sf::Vector2f v);
    sf::Vector2f Vector2DtosfmlVector2D(Plain::Vector2D v);

    float Length(Vector2D v);
    float Distance(Vector2D a, Vector2D b);
    Vector2D Normalize(Vector2D v);
    float DotProduct(Vector2D a, Vector2D b);
    float CrossProduct(Vector2D a, Vector2D b);
}