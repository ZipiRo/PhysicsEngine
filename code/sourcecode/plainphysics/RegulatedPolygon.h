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
