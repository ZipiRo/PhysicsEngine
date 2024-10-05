#pragma once

namespace PlainPhysics{
    class World
    {
        public:
            World();

            int BodyCount();
            void AddBody(Body *body);
            void RemoveBody(Body *body);
            Body* GetBody(int index);
            void Step(float delta);

        private:
            std::list<Body *> bodyList;
            Vector2D gravity;
    };
}