#include <PlainEngine.h>
#include <PlainPhysics.h>

using namespace PlainEngine;
using namespace PlainPhysics;

class Game : public Engine
{
    public:
        Game()
        {
            w_Name = "PhysicsEngine v1.0";
            w_BackgroundColor = sf::Color(30.0f, 129.0f, 176.0f);
            viewZoomFactor = 0.1f;
            maxFps = 9999.0f;
        }
    
    private:
        World world = World();
        bool lPressed = false;
        int currentBody = Body::RectangleShape;

        void Create() override 
        {
            Body *Ground = new Rectangle(78.0f, 10.0f, Vector2D(this->GetWindowWidth() / 2.0f, this->GetWindowHeigth() / 2 + 20.0f), 1.0f, 0.5f, sf::Color(71.0f, 135.0f, 70.0f), sf::Color::Transparent, true);
            world.AddBody(Ground);
        }

        void Update(float delta) override 
        {   
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(!lPressed)
                {
                    CreateBody();
                    lPressed = true;
                }
            }
            else {
                if(lPressed) lPressed = false;
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
            {
                currentBody = Body::RectangleShape;
                std::cout << "CREATING RECTANGLES" << '\n';
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
            {
                currentBody = Body::CircleShape;
                std::cout << "CREATING CIRCLES" << '\n';
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
            {
                currentBody = Body::RegulatedPolygonShape;
                std::cout << "CREATING REGULATEDPOLYGONS" << '\n';
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::B))
            {
                std::cout << "Bodyes:" << this->world.BodyCount() << '\n';
            }

            this->world.Step(delta, 20);

            float bottomWindow = this->GetWindowHeigth();
            for(int i = 1; i <= this->world.BodyCount(); i++)
            {
                Body *body = this->world.GetBody(i);
                AABB aabb = body->GetAABB();

                if(aabb.max.y > bottomWindow)
                {
                    this->world.RemoveBody(body);
                }
            }
        }  

        void Draw(sf::RenderWindow& window) override
        {   
            for(int i = 1; i <= this->world.BodyCount(); i++)
            {
                this->world.GetBody(i)->Draw(window);
            }
        }

        void CreateBody()
        {
            int r = 0 + rand() % (255 - 0 + 1);
            int g = 0 + rand() % (255 - 0 + 1);
            int b = 0 + rand() % (255 - 0 + 1);

            if(currentBody == Body::RectangleShape)
            {
                float width = 1 + rand() % (3 - 1 + 1);
                float height = 1 + rand() % (3 - 1 + 1);

                Body *body = new Rectangle(width, height, VectorMath::sfmlVector2DtoVector2D(this->mouseWorldPos), 1.0f, 0.5f, sf::Color(r, g, b), sf::Color::Transparent, false);
                this->world.AddBody(body);
            }
            else if(currentBody == Body::CircleShape)
            {
                float radius = 1 + rand() % (3 - 1 + 1);

                Body *body = new Circle(radius, VectorMath::sfmlVector2DtoVector2D(this->mouseWorldPos), 1.0f, 0.5f, sf::Color(r, g, b), sf::Color::Transparent, false);
                this->world.AddBody(body);
            }
            else if(currentBody == Body::RegulatedPolygonShape)
            {
                float sides = 3 + rand() % (6 - 10 + 1);
                float radius = 1 + rand() % (3 - 1 + 1);

                Body *body = new RegulatedPolygon(sides, radius, VectorMath::sfmlVector2DtoVector2D(this->mouseWorldPos), 1.0f, 0.5f, sf::Color(r, g, b), sf::Color::Transparent, false);
                this->world.AddBody(body);
            }
        }
};

int main()
{
    Game game;
    game.Construct(1240, 720);
    game.Start();
}
