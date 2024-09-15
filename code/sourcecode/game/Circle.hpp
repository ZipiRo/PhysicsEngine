namespace Plain{
    class Circle : public Body
    {
        public:
            Circle(float, Vector2D, float, float, sf::Color, sf::Color, bool);

        private:
            sf::CircleShape circle;
    };
}