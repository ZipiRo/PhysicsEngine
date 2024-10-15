#include "Circle.h"

const float PI = 3.141592f;

namespace PlainPhysics 
{
    AABB UpdateCircleAABB(Vector2D position, float radius) 
    {
        float minX = position.x - radius;
        float minY = position.y - radius;

        float maxX = position.x + radius;
        float maxY = position.y + radius;
        
        return AABB(minX, minY, maxX, maxY);
    }

    Circle::Circle(float radius, Vector2D position, float density, float restitution, sf::Color fillColor, sf::Color outlineColor, bool isStatic)
    {
        this->position = position;
        this->linearVelocity = Vector2D(0, 0);
        this->angle = 0.0f;
        this->angularVelocity = 0.0f;
        
        this->force = Vector2D(0, 0);

        this->radius = radius;
        this->surface = this->radius * this->radius * PI;
        this->density = density;
        this->mass = isStatic ? 0.0f : this->surface * this->density;
        this->inertia = isStatic ? 0.0f : (1.0f / 2.0f) * this->mass * (this->radius * this->radius);
        this->restitution = restitution;
        this->staticFriction = 0.6f;
        this->dinamicFriction = 0.4f;

        this->invMass = isStatic ? 0.0f : 1.0f / mass;
        this->invInertia = isStatic ? 0.0f : 1.0f / inertia;

        this->fillColor = fillColor;
        this->outlineColor = outlineColor;

        this->isStatic = isStatic;

        this->shapeType = CircleShape;

        this->aabb = UpdateCircleAABB(this->position, this->radius);

        this->circleShape = sf::CircleShape(this->radius);
        this->circleShape.setOrigin(sf::Vector2f(this->radius, this->radius));
        this->circleShape.setFillColor(this->fillColor);
        this->circleShape.setOutlineColor(this->outlineColor);
        this->circleShape.setOutlineThickness(1);

        this->shape = &this->circleShape;
    }

    void Circle::Draw(sf::RenderWindow& window)
    {
        if(this->UPDATE_AABB)
            this->aabb = UpdateCircleAABB(this->position, this->radius);

        this->circleShape.setPosition(VectorMath::Vector2DtosfmlVector2D(this->position));
        this->circleShape.setRotation(this->angle);

        window.draw(this->circleShape);
    }

    std::vector<Vector2D> Circle::GetTransformedVertices()
    {
        return std::vector<Vector2D>();
    }

    AABB Circle::GetAABB()
    {
        if(this->UPDATE_AABB)
            this->aabb = UpdateCircleAABB(this->position, this->radius);

        this->UPDATE_AABB = false;
        return this->aabb;
    }
}