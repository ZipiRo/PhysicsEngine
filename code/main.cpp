#include <PlainEngine.h>
#include <PlainPhysics.h>

using namespace PlainEngine;
using namespace PlainPhysics;

const float pixelsPerMeter = 10.0f;

class Game : public Engine
{
    public:
        Game()
        {
            w_Name = "PhysicsEngine v1.0";
            w_BackgroundColor = sf::Color::Black;
            viewZoomFactor = 1.0f / pixelsPerMeter;
            maxFps = 60.9f;
        }
    
    private:
        World world;
        bool lPressed = false;
        int currentBody = 1;

        void Create() override 
        {
            Body *Ground = new Rectangle(80.0f, 3.0f, Vector2D(this->GetWindowWidth() / 2.0f, this->GetWindowHeigth() / 2 + 20.0f), 1.0f, 0.5f, sf::Color::White, sf::Color::Transparent, true);
            world.AddBody(Ground);

            Body *Platform_One = new Rectangle(35.0f, 3.0f, Vector2D(this->GetWindowWidth() / 2.0f - 18.0f, this->GetWindowHeigth() / 2 - 10.0f), 1.0f, 0.5f, sf::Color::White, sf::Color::Transparent, true);
            Platform_One->RotateTo(25.0f);
            world.AddBody(Platform_One);
            
            Body *Platform_Two = new Rectangle(40.0f, 3.0f, Vector2D(this->GetWindowWidth() / 2.0f + 40.0f, this->GetWindowHeigth() / 2), 1.0f, 0.5f, sf::Color::White, sf::Color::Transparent, true);
            Platform_Two->RotateTo(90.0f);
            world.AddBody(Platform_Two);
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
                currentBody = 1;
                std::cout << "CREATING RECTANGLES" << '\n';
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
            {
                currentBody = 2;
                std::cout << "CREATING CIRCLES" << '\n';
            }
            // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
            // {
            //     currentBody = 3;
            //     std::cout << "CREATING REGULATEDPOLYGONS" << '\n';
            // }
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
            Body *body;

            int r = 0 + rand() % (255 - 0 + 1);
            int g = 0 + rand() % (255 - 0 + 1);
            int b = 0 + rand() % (255 - 0 + 1);

            if(currentBody == 1)
            {
                float width = 3 + rand() % (5 - 3 + 1);
                float height = 3 + rand() % (5 - 3 + 1);

                body = new Rectangle(width, height, VectorMath::sfmlVector2DtoVector2D(this->mouseWorldPos), 1.0f, 0.5f, sf::Color(r, g, b), sf::Color::Transparent, false);
                this->world.AddBody(body);
            }
            else if(currentBody == 2)
            {
                float radius = 2 + rand() % (3 - 2 + 1);

                body = new Circle(radius, VectorMath::sfmlVector2DtoVector2D(this->mouseWorldPos), 1.0f, 0.5f, sf::Color(r, g, b), sf::Color::Transparent, false);
                this->world.AddBody(body);
            }
            // else if(currentBody == 3)
            // {
            //     float sides = 3 + rand() % (6 - 10 + 1);
            //     float radius = 1 + rand() % (3 - 1 + 1);

            //     Body *body = new RegulatedPolygon(sides, radius, VectorMath::sfmlVector2DtoVector2D(this->mouseWorldPos), 1.0f, 0.5f, sf::Color(r, g, b), sf::Color::Transparent, false);
            //     this->world.AddBody(body);
            // }
        }
};

int main()
{
    Game game;
    game.Construct(1280, 720);
    game.Start();
}
