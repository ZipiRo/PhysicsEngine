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

            void Move(Vector2D amouunt);
            void MoveTo(Vector2D position);
            void Rotate(float amouunt);
            void RotateTo(float angle);

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