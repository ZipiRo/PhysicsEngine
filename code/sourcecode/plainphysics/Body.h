#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <list>

#include "Vector2D.h"
#include "AABB.h"

namespace PlainPhysics
{
    class Body
    {
        public:
            enum { PolygonShape, CircleShape};

            void Move(Vector2D amount);
            void MoveTo(Vector2D position);
            void Rotate(float amount);
            void RotateTo(float angle);
            void AddForce(Vector2D amount);

            void SetFillColor(sf::Color color);
            void SetOutlineColor(sf::Color color);
            void Step(float delta, int totalIterations);
            
            Vector2D position;
            Vector2D linearVelocity;
            float angle;
            float angularVelocity;

            Vector2D force;

            float width;
            float height;
            float radius;

            float inertia;
            float invInertia;

            float surface;
            float density;
            float mass;
            float invMass;
            float restitution;
            float area;

            bool isStatic;


            bool UPDATE_VERTICES;
            bool UPDATE_AABB;

            sf::Color fillColor;
            sf::Color outlineColor;
            sf::Shape* shape;

            int shapeType;

            Body();
            
		    virtual void Draw(sf::RenderWindow&) = 0;
            virtual std::vector<Vector2D> GetTransformedVertices() = 0;
            virtual AABB GetAABB() = 0;
    };
}