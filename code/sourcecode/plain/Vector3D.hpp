namespace Plain{    
    class Vector3D {
    public:
        float x, y, z;

        Vector3D();

        Vector3D(float x, float y, float z);

        Vector3D operator= (Vector3D b);
        Vector3D operator+ (Vector3D b);
        Vector3D operator- (Vector3D b);
        Vector3D operator+= (Vector3D b);
        Vector3D operator-= (Vector3D b);
        Vector3D operator* (float scalar);
        Vector3D operator/ (float scalar);
        Vector3D operator*= (float scalar);
        Vector3D operator/= (float scalar);
    };

    Vector3D multipyVector3D(Vector3D a, Vector3D b);
    Vector3D divideVector3D(Vector3D a, Vector3D b);

    Plain::Vector3D sfmlVector3DtoVector3D(sf::Vector3f v);
    sf::Vector3f Vector3DtosfmlVector3D(Plain::Vector3D v);
}