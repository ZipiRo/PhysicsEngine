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

    Plain::Vector3D sfmlVector3DtoVector3D(sf::Vector3f);
    sf::Vector3f Vector3DtosfmlVector3D(Plain::Vector3D);
}