#pragma once

namespace Plain{
    class Rectangle : public Body
    {
        public:
            Rectangle (float width, float height, Vector2D position, float density, float restitution, sf::Color fillColor, sf::Color outlineColor, bool isStatic);
            
            void Draw(sf::RenderWindow& window) override;
            LinkedList<Vector2D> GetTransformedVertices();

        private:
            sf::RectangleShape rectangleShape;
            
            Plain::LinkedList<Vector2D> vertices;
            Plain::LinkedList<Vector2D> transformedVertices;
    };

    LinkedList<Vector2D> CreateBoxVertices(float width, float heigth);
}