namespace PlainPhysics
{
    class RegulatedPolygon : public Body
    {
        public:
            RegulatedPolygon (int sides, float scale, Vector2D position, float density, float restitution, sf::Color fillColor, sf::Color outlineColor, bool isStatic);
            
            void Draw(sf::RenderWindow& window) override;
            std::list<Vector2D> GetTransformedVertices() override;

        private:
            sf::ConvexShape polygonShape;
            
            std::list<Vector2D> vertices;
            std::list<Vector2D> transformVertices;
    };
}
