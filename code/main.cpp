#include <PlainEngine.h>
#include <PlainPhysics.h>

using namespace PlainEngine;
using namespace PlainPhysics;

class Game : public Engine
{
    public:
        Game()
        {
            w_Name = "PhysicsEngine 1.0";
            w_BackgroundColor = sf::Color::Black;

            maxFps = 60.0f;
        }
    
    private:
        Body* player;
        World world = World();
        int bodyCount = 10;

        void Create() override 
        {
            srand(time(0));
 
            for(int i = 0; i < bodyCount; i++)
            {
                int shapeType = rand() % 2;
                int isStatic = (!i) ? 0 : rand() % 2;

                Body *body;

                int x = rand() % this->GetWidth();
                int y = rand() % this->GetHeigth();
                int radius = rand() % 15 + 10;

                if(shapeType == Body::RectangleShape)
                {
                    body = new Rectangle(radius + 10, radius + 10, Vector2D(x, y), 2.0f, 0.5f, sf::Color::Transparent, sf::Color::White, isStatic);
                }
                else if(shapeType == Body::CircleShape)
                {
                    body = new Circle(radius, Vector2D(x, y), 2.0f, 0.5f, sf::Color::Transparent, sf::Color::White, isStatic);
                }

                if(isStatic)
                    body->SetFillColor(sf::Color::White);

                this->world.AddBody(body);
            }

            this->player = world.GetBody(1);
        }

        float forceMagnitude = 50.0f;

        void Update(float delta) override 
        {
            Vector2D direction;

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || 
                sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                direction.y--;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || 
                sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                direction.y++;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || 
                sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                direction.x--;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || 
                sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                direction.x++;
                
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
                this->player->Rotate(-45 * delta);

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::T))
                this->player->Rotate(45 * delta);

            if(direction.x != 0 || direction.y != 0)
            {
                Vector2D forceDirection = VectorMath::Normalize(direction);
                Vector2D force = forceDirection * forceMagnitude * 10000.0f;

                this->player->AddForce(force);
            }   

            this->world.Step(delta);
        }  

        void Draw(sf::RenderWindow& window) override
        {   
            for(int i = 1; i <= this->world.BodyCount(); i++)
            {
                this->world.GetBody(i)->Draw(window);
            }
        }
};

int main()
{
    Game game;
    game.Construct(1240, 720);
    game.Start();
}
