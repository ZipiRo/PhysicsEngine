#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Color.hpp>
#include <vector>

#include "Vector2D.h"
#include "AABB.h"
#include "Body.h"

namespace PlainPhysics
{
    struct Point
    {
        Vector2D position;
        Body *body;
        int index;
    };    

    class RectangleBoundry
    {   
        public:
            Vector2D position;
            float width, height;

            RectangleBoundry();
            RectangleBoundry(Vector2D position, float width, float height);
            RectangleBoundry(float x, float y, float width, float height);

            bool Contains(Vector2D position);
            bool Intersects(AABB bounds);
    };
    

    class QuadTree
    {
        public:
            QuadTree();
            QuadTree(RectangleBoundry bounds, int capacity);

            void Insert(Point point);
            void Querry(AABB bounds, std::vector<Point>& foundPoints);
            void clear();

            void Show(sf::RenderWindow& window);
        private:
            void SubDivide();
            RectangleBoundry boundry; 
            std::vector<Point> points;
            int capacity;
            bool divided;

            QuadTree *northest;
            QuadTree *northwest;
            QuadTree *southwest;
            QuadTree *southest;
    };
}