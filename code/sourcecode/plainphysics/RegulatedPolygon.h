#pragma once
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Color.hpp>
#include <list>
#include <cmath>

#include "Vector2D.h"
#include "Transform.h"
#include "VectorMath.h"
#include "AABB.h"
#include "Body.h"

namespace PlainPhysics
{
    class RegulatedPolygon : public Body
    {
        public:
            RegulatedPolygon (int sides, float radius, Vector2D position, float density, float restitution, sf::Color fillColor, sf::Color outlineColor, bool isStatic);
            
            void Draw(sf::RenderWindow& window) override;
            std::list<Vector2D> GetTransformedVertices() override;
            AABB GetAABB() override;

        private:
            sf::ConvexShape polygonShape;
            
            std::list<Vector2D> vertices;
            std::list<Vector2D> transformVertices;

            AABB aabb;
    };
}
