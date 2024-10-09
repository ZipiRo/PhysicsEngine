#include "RegulatedPolygon.h"

const float max_float = 1000000.0f;
const float min_float = -1000000.0f;

namespace PlainPhysics 
{
    std::list<Vector2D> CreateRegulatedPolygonVertices(int sides, float radius)
    {
        std::list<Vector2D> vertices;

        for(int i = 0; i < sides; i++)
        {
            float e = 2 * i * 3.141592f;
            float vertexX = cosf((e + 1) / float(sides)) * radius; 
            float vertexY = sinf((e + 1) / float(sides)) * radius;

            vertexX *= 1.0f;
            vertexY *= 1.0f;

            vertices.push_back(Vector2D(vertexX, vertexY));
        }

        return vertices;
    }

    AABB UpdateRegulatedPolygonAABB(Vector2D position, float radius) 
    {
        float minX = position.x - radius;
        float minY = position.y - radius;

        float maxX = position.x + radius;
        float maxY = position.y + radius;
        
        return AABB(minX, minY, maxX, maxY);
    }
    
    std::list<Vector2D> UpdateRegulatedPolygonVertices(std::list<Vector2D> vertices, Vector2D position, float angle)
    {
        std::list<Vector2D> transformVertices;

        Transform transform(position, angle);

        for(Vector2D v : vertices)
            transformVertices.push_back(VectorMath::VectorTransformZ(v, transform));

        return transformVertices;
    }

    RegulatedPolygon::RegulatedPolygon (int sides, float radius, Vector2D position, float density, float restitution, sf::Color fillColor, sf::Color outlineColor, bool isStatic)
    {
        this->position = position;
        this->linearVelocity = Vector2D(0, 0);
        this->angle = 0.0f;
        this->angularVelocity = 0.0f;

        this->force = Vector2D(0, 0);

        this->radius = radius;
        this->surface = sides * (radius * radius) * sinf(2 * 3.141592f / sides) / 2;

        this->density = density;
        this->mass = isStatic ? INFINTE_MASS : this->surface * this->density;
        this->invMass = 1.0f / mass;
        this->restitution = restitution;

        this->fillColor = fillColor;
        this->outlineColor = outlineColor;

        this->isStatic = isStatic;

        this->shapeType = Body::RegulatedPolygonShape;

        this->vertices = CreateRegulatedPolygonVertices(sides, radius);
        this->transformVertices = this->vertices;

        this->aabb = UpdateRegulatedPolygonAABB(this->position, this->radius);

        this->polygonShape = sf::ConvexShape(sides);

        int index = 0;
        for(Vector2D vertex : vertices)
            this->polygonShape.setPoint(index++, VectorMath::Vector2DtosfmlVector2D(vertex));

        this->polygonShape.setFillColor(this->fillColor);
        this->polygonShape.setOutlineColor(this->outlineColor);
        this->polygonShape.setOutlineThickness(1);
        this->shape = &this->polygonShape;

        this->UPDATE_VERTICES = true;
        this->UPDATE_AABB = true;
    }

    void RegulatedPolygon::Draw(sf::RenderWindow& window)
    {   
        if(this->UPDATE_VERTICES)
            this->transformVertices = UpdateRegulatedPolygonVertices(this->vertices, this->position, this->angle);

        if(this->UPDATE_AABB)
            this->aabb = UpdateRegulatedPolygonAABB(this->position, this->radius);

        this->polygonShape.setPosition(VectorMath::Vector2DtosfmlVector2D(this->position));
        this->polygonShape.setRotation(this->angle);

        window.draw(this->polygonShape);

        this->UPDATE_VERTICES = false;
    }

    std::list<Vector2D> RegulatedPolygon::GetTransformedVertices()
    {
        if(this->UPDATE_VERTICES)
            this->transformVertices = UpdateRegulatedPolygonVertices(this->vertices, this->position, this->angle);

        this->UPDATE_VERTICES = false;
        return this->transformVertices;
    }  

    AABB RegulatedPolygon::GetAABB()
    {
        if(this->UPDATE_AABB)
            this->aabb = UpdateRegulatedPolygonAABB(this->position, this->radius);

        this->UPDATE_AABB = false;
        return this->aabb;
    } 
}