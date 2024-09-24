#pragma once

namespace Plain{
    enum{
        RectangleShape,
        CircleShape,
        Polygon
    };

    class Body
    {
        public:void Move(Vector2D amouunt);
            void MoveTo(Vector2D position);
            void Rotate(float amouunt);
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
            virtual Vector2D* GetTransformedVertices() = 0;
    };

}