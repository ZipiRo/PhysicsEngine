#pragma once
#include "Vector2D.h"
#include "Transform.h"
#include "VectorMath.h"
#include "AABB.h"
#include "Body.h"
#include "Manifold.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Collisions.h"

namespace PlainPhysics{
    class World
    {
        public:
            World();

            int BodyCount();
            void AddBody(Body *body);
            void RemoveBody(Body *body);
            Body* GetBody(int index);
            void Step(float delta, int totalItterations);

        private:
            std::list<Body *> bodyList;
            std::list<Manifold> contactList;
            Vector2D gravity;
    };
}