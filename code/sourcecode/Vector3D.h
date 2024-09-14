namespace Plain{    
    class Vector3D {
    public:
        float x, y, z;

        Vector3D();

        Vector3D(float, float, float);

        Vector3D operator= (Vector3D);
        Vector3D operator+ (Vector3D);
        Vector3D operator- (Vector3D);
        Vector3D operator+= (Vector3D);
        Vector3D operator-= (Vector3D);
        Vector3D operator* (float);
        Vector3D operator/ (float);
        Vector3D operator*= (float);
        Vector3D operator/= (float);
    };

    Vector3D multipyVector3D(Vector3D, Vector3D);
    Vector3D divideVector3D(Vector3D, Vector3D);

    // Plain::Vector2D sfmlVector2DtoVector2D(sf::Vector2f v)
    // sf::Vector2f Vector2DtosfmlVector2D(Plain::Vector2D v)
}