#include <SFML/System/Vector2.hpp>
#include <cmath>

#include "Vector2D.hpp"

namespace Plain
{
    Vector2D::Vector2D() {
        this->x = 0;
        this->y = 0;
    }

    Vector2D::Vector2D(float x, float y) {
        this->x = x;
        this->y = y;
    }

    Vector2D Vector2D::operator= (Vector2D b) {
        this->x = b.x;
        this->y = b.y;
        return *this;
    }

    Vector2D Vector2D::operator+ (Vector2D b) {
        return Vector2D(this->x + b.x, this->y + b.y);
    }

    Vector2D Vector2D::operator- (Vector2D b) {
        return Vector2D(this->x - b.x, this->y - b.y);
    }

    Vector2D Vector2D::operator+= (Vector2D b) {
        this->x += b.x;
        this->y += b.y;
        return *this;
    }

    Vector2D Vector2D::operator-= (Vector2D b) {
        this->x -= b.x;
        this->y -= b.y;
        return *this;
    }

    Vector2D Vector2D::operator* (float scalar) {
        return Vector2D(this->x * scalar, this->y * scalar);
    }

    Vector2D Vector2D::operator/ (float scalar) {
        return Vector2D(this->x / scalar, this->y / scalar);
    }

    Vector2D Vector2D::operator*= (float scalar) {
        this->x *= scalar;
        this->y *= scalar;
        return *this;
    }

    Vector2D Vector2D::operator/= (float scalar) {
        this->x /= scalar;
        this->y /= scalar;
        return *this;
    }

    Vector2D Vector2D::Zero (){
        return Vector2D(0, 0);
    }

    Vector2D multipyVector2D(Vector2D a, Vector2D b) {
        return Vector2D(a.x * b.x, a.y * b.y);
    }

    Vector2D divideVector2D(Vector2D a, Vector2D b) {
        return Vector2D(a.x / b.x, a.y / b.y);
    }

    float length(Vector2D v){
        return sqrt(v.x * v.x + v.y * v.y);
    }

    float distance(Vector2D a, Vector2D b){
        float dx = a.x - b.x;
        float dy = a.y - b.y;

        return sqrt(dx * dx + dy * dy);
    }

    Vector2D normalize(Vector2D v){
        float len = length(v);
        return Vector2D(v.x / len, v.y / len);
    }

    float dotProduct(Vector2D a, Vector2D b){
        return a.x * b.x + a.y * b.y;
    }

    float crossProduct(Vector2D a, Vector2D b){
        return a.x * b.y - a.y * b.x;
    }

    
    Plain::Vector2D sfmlVector2DtoVector2D(sf::Vector2f v){
        return Plain::Vector2D(v.x, v.y);
    }

    sf::Vector2f Vector2DtosfmlVector2D(Plain::Vector2D v){
        return sf::Vector2f(v.x, v.y);
    }
}