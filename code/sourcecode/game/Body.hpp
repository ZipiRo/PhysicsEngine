namespace Plain{
    enum{
        RectangleShape,
        CircleShape
    };

    class Body
    {
        public:
            Body();
            
		    virtual void Draw(sf::RenderWindow&) = 0;

            Vector2D position;
            Vector2D linearVelocity;
            float angle;
            float angularVelocity;

            float surface;
            float density;
            float mass;
            float restitution;
            float area;

            bool isStatic;

            float radius;
            float width;
            float height;

            sf::Color fillColor;
            sf::Color outlineColor;

            int type;
            
        private:
    };
}