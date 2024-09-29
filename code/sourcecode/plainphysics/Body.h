#pragma once

namespace PlainPhysics
{
    class Body
    {
        public:
            enum { RectangleShape, CircleShape, Polygon };
            void Move(Vector2D amount);
            void MoveTo(Vector2D position);
            void Rotate(float amount);
            void RotateTo(float angle);
            void SetFillColor(sf::Color color);
            void SetOutlineColor(sf::Color color);

            Vector2D position;
            Vector2D linearVelocity;
            float angle;
            float angularVelocity;

            float surface;
            float density;
            float mass;
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

            int type;

            Body();
            
		    virtual void Draw(sf::RenderWindow&) = 0;
            virtual std::list<Vector2D> GetTransformedVertices() = 0;
    };

}