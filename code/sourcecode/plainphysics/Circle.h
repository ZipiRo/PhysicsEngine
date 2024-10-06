#pragma once

namespace PlainPhysics
{
    class Circle : public Body
    {
        public:
            Circle(float radius, Vector2D position, float density, float restitution, sf::Color fillColor, sf::Color outlineColor, bool isStatic);

            void Draw(sf::RenderWindow&) override;
            std::list<Vector2D> GetTransformedVertices() override;
            AABB GetAABB() override;

        private:
            sf::CircleShape circleShape;

            AABB aabb;
    };
}