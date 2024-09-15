namespace Plain{
    class Rectangle : public Body
    {
        public:
            Rectangle (float, float, Vector2D, float, float, sf::Color, sf::Color, bool);
            
            void Draw(sf::RenderWindow&) override;

        private:
            sf::RectangleShape rectangle;

            Vector2D vertices[4];
            Vector2D transformedVertices[4];
    };
}