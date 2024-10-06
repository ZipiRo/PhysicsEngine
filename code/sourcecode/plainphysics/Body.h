#pragma once

namespace PlainPhysics
{
    class Body
    {
        public:
            enum { RectangleShape, CircleShape, RegulatedPolygonShape};

            void Move(Vector2D amount);
            void MoveTo(Vector2D position);
            void Rotate(float amount);
            void RotateTo(float angle);
            void AddForce(Vector2D amount);

            void SetFillColor(sf::Color color);
            void SetOutlineColor(sf::Color color);
            void SetStatic(bool isStatic);
            void Step(float delta, int totalItterations);
            
            Vector2D position;
            Vector2D linearVelocity;
            float angle;
            float angularVelocity;

            Vector2D force;

            float surface;
            float density;
            float mass;
            float invMass;
            float restitution;
            float area;

            bool isStatic;

            float radius;
            float width;
            float height;

            bool UPDATE_VERTICES;
            bool UPDATE_AABB;

            sf::Color fillColor;
            sf::Color outlineColor;
            sf::Shape* shape;

            int shapeType;

            Body();
            
		    virtual void Draw(sf::RenderWindow&) = 0;
            virtual std::list<Vector2D> GetTransformedVertices() = 0;
            virtual AABB GetAABB() = 0;
    };
}