#pragma once

namespace Plain{
    class Circle : public Body
    {
        public:
            Circle(float radius, Vector2D position, float density, float restitution, sf::Color fillColor, sf::Color outlineColor, bool isStatic);

            void Draw(sf::RenderWindow&) override;

        private:
            sf::CircleShape circle;
    };
}