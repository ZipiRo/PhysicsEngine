#pragma once

namespace PlainPhysics
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
}