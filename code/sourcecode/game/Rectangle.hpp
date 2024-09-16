#pragma once

namespace Plain{
    class Rectangle : public Body
    {
        public:
            Rectangle (float width, float height, Vector2D position, float density, float restitution, sf::Color fillColor, sf::Color outlineColor, bool isStatic);
            
            void Draw(sf::RenderWindow& window) override;

        private:
            sf::RectangleShape rectangle;

            Vector2D vertices[4];
            Vector2D transformedVertices[4];
    };
}