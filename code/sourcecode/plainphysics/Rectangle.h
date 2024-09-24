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
                Vector2D* GetTransformedVertices() override;

            private:
                sf::RectangleShape rectangleShape;
                
                Vector2D vertices[4];
                Vector2D transformVertices[4];
        };

        Vector2D* CreateRectangleVertices(float width, float heigth);
        Vector2D* UpdateVertices(Vector2D* vertices, Vector2D position, float angle);
    }
}