#pragma once

namespace plain
{
    namespace body
    {
        class Circle : public Body
        {
            public:
                Circle(float radius, Vector2D position, float density, float restitution, sf::Color fillColor, sf::Color outlineColor, bool isStatic);

                void Draw(sf::RenderWindow&) override;
                std::list<Vector2D> GetTransformedVertices() override;

            private:
                sf::CircleShape circleShape;
        };
    }
}