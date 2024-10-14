#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Color.hpp>
#include <vector>

#include "Vector2D.h"
#include "Transform.h"
#include "VectorMath.h"
#include "AABB.h"
#include "Body.h"

namespace PlainPhysics
{
    class Rectangle : public Body
    {
        public:
            Rectangle (float width, float height, Vector2D position, float density, float restitution, sf::Color fillColor, sf::Color outlineColor, bool isStatic);
            
            void Draw(sf::RenderWindow& window) override;
            std::vector<Vector2D> GetTransformedVertices() override;
            AABB GetAABB() override;

        private:
            sf::RectangleShape rectangleShape;
            
            std::vector<Vector2D> vertices;
            std::vector<Vector2D> transformVertices;
            
            AABB aabb;
    };
}