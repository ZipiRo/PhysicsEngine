#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <list>

#include "Vector2D.h"
#include "Transform.h"
#include "VectorMath.h"
#include "AABB.h"
#include "Body.h"

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