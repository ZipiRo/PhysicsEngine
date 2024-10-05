namespace PlainPhysics
{
    class Polygon : public Body
    {
        public:
            Polygon (int sides, float scale, Vector2D position, float density, float restitution, sf::Color fillColor, sf::Color outlineColor, bool isStatic);
            
            void Draw(sf::RenderWindow& window) override;
            std::list<Vector2D> GetTransformedVertices() override;

        private:
            sf::ConvexShape polygonShape;
            
            std::list<Vector2D> vertices;
            std::list<Vector2D> transformVertices;
    };
}
