#pragma once

namespace plain
{
    namespace body
    {
        class Rectangle : public Body
        {
            public:
                Rectangle (float width, float height, Vector2D position, float density, float restitution, sf::Color fillColor, sf::Color outlineColor, bool isStatic);
                
                void Draw(sf::RenderWindow& window) override;
                std::list<Vector2D> GetTransformedVertices() override;

            private:
                sf::RectangleShape rectangleShape;
                
                std::list<Vector2D> vertices;
                std::list<Vector2D> transformVertices;
        };

        std::list<Vector2D> CreateRectangleVertices(float width, float heigth);
        std::list<Vector2D> UpdateVertices(std::list<Vector2D> vertices, Vector2D position, float angle);
    }
}