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

namespace PlainPhysics
{
    struct ContactPair { int first, second; };

    class World
    {
        public:
            World();

            int BodyCount();
            void AddBody(Body *body);
            void RemoveBody(Body *body);
            Body* GetBody(int index);
            void Step(float delta, int totalIterations);
            void StepBodies(float delta, int totalIterations);
            void BroadPhase();
            void NarrowPhase();

        private:
            Vector2D gravity;
            std::list<Body *> bodyList;
            std::vector<ContactPair> contactPairs;
    };
}