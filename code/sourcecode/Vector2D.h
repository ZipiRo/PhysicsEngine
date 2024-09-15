namespace Plain
{
    class Vector2D {
    public:
        float x, y;

        Vector2D();
        Vector2D(float, float);

        Vector2D operator= (Vector2D);
        Vector2D operator+ (Vector2D);
        Vector2D operator- (Vector2D);
        Vector2D operator+= (Vector2D);
        Vector2D operator-= (Vector2D);
        Vector2D operator* (float);
        Vector2D operator/ (float);
        Vector2D operator*= (float);
        Vector2D operator/= (float);
    };

    Vector2D multipyVector2D(Vector2D, Vector2D);
    Vector2D divideVector2D(Vector2D, Vector2D);

    Plain::Vector2D sfmlVector2DtoVector2D(sf::Vector2f);
    sf::Vector2f Vector2DtosfmlVector2D(Plain::Vector2D);

    float length(Vector2D);
    float distance(Vector2D, Vector2D);
    Vector2D normalize(Vector2D);
    float dotProduct(Vector2D, Vector2D);
    float crossProduct(Vector2D, Vector2D);
}