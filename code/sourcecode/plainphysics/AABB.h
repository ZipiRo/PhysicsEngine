#pragma once

namespace PlainPhysics
{
    class AABB
    {
        public:
            Vector2D min;
            Vector2D max;

            AABB ();
            AABB (Vector2D min, Vector2D max);
            AABB (float minX, float minY, float maxX, float maxY);
    };
}