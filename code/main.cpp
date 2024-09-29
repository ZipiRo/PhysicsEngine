#include "sourcecode/plainengine/PlainEngine.h"
#include "sourcecode/plainphysics/PlainPhysics.h"

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
        std::list<Body *> bodyList; 
        int bodyCount = 10;

        void Create() override 
        {
            srand(time(0));
 
            for(int i = 0; i < bodyCount; i++)
            {
                int shapeType = rand() % 2;

                Body *body;

                int x = rand() % this->GetWidth();
                int y = rand() % this->GetHeigth();
                int radius = rand() % 15 + 10;

                if(shapeType == Body::RectangleShape)
                {
                    body = new Rectangle(radius + 10, radius + 10, Vector2D(x, y), 2.0f, 0.5f, sf::Color::Transparent, sf::Color::White, false);
                }
                else if(shapeType == Body::CircleShape)
                {
                    body = new Circle(radius, Vector2D(x, y), 2.0f, 0.5f, sf::Color::Transparent, sf::Color::White, false);
                }

                bodyList.push_back(body);
            }
        }

        void Update(float delta) override 
        {
            Vector2D direction;

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                direction.y--;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                direction.y++;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                direction.x--;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                direction.x++;

            if(direction.x != 0 || direction.y != 0)
            {
                direction = vectormath::Normalize(direction);
                PlainPhysics::Vector2D velocity = direction * 200.0f * delta;

                bodyList.front()->Move(velocity);
            }

            for(Body* body : bodyList)
            {
                body->SetOutlineColor(sf::Color::White);
                // body->Rotate(-45 * delta);
            }

            for(auto body_it = bodyList.begin(), body_it_ = body_it; body_it != --bodyList.end(); ++body_it)
            {
                Body* bodyA = *(body_it);    

                for(auto body_jt = ++body_it_; body_jt != bodyList.end(); ++body_jt)
                {
                    Body* bodyB = *(body_jt);

                    Vector2D normal; float depth;
                    
                    if(bodyA->type == Body::RectangleShape && bodyB->type == Body::CircleShape)
                        if(collisions::IntersectCirclesPolygons(bodyB->position, bodyB->radius, bodyA->GetTransformedVertices(), bodyA->position, normal, depth))
                        {
                            if(vectormath::NAN_Values(normal)) continue;
                            bodyA->SetOutlineColor(sf::Color::Red);
                            bodyB->SetOutlineColor(sf::Color::Red);
                            bodyA->Move(normal * depth / 2.0f);
                            bodyB->Move((normal * -1.0f) * depth / 2.0f);
                        }

                    if(bodyA->type == Body::CircleShape && bodyB->type == Body::RectangleShape)
                        if(collisions::IntersectCirclesPolygons(bodyA->position, bodyA->radius, bodyB->GetTransformedVertices(), bodyB->position, normal, depth))
                        {
                            if(vectormath::NAN_Values(normal)) continue;
                            bodyA->SetOutlineColor(sf::Color::Red);
                            bodyB->SetOutlineColor(sf::Color::Red);
                            bodyA->Move((normal * -1.0f) * depth / 2.0f);
                            bodyB->Move(normal * depth / 2.0f);
                        }

                    if(bodyA->type == Body::CircleShape && bodyB->type == Body::CircleShape)
                        if(collisions::IntersectCircles(bodyA->position, bodyA->radius, bodyB->position, bodyB->radius, normal, depth))
                        {
                            if(vectormath::NAN_Values(normal)) continue;
                            bodyA->SetOutlineColor(sf::Color::Red);
                            bodyB->SetOutlineColor(sf::Color::Red);
                            bodyA->Move((normal * -1.0f) * depth / 2.0f);
                            bodyB->Move(normal * depth / 2.0f);
                        }
                        
                    if(bodyA->type == Body::RectangleShape && bodyB->type == Body::RectangleShape)
                        if(collisions::IntersectPolygons(bodyA->GetTransformedVertices(), bodyA->position, bodyB->GetTransformedVertices(), bodyB->position, normal, depth))
                        {
                            if(vectormath::NAN_Values(normal)) continue;
                            bodyA->SetOutlineColor(sf::Color::Red);
                            bodyB->SetOutlineColor(sf::Color::Red);
                            bodyA->Move((normal * -1.0f) * depth / 2.0f);
                            bodyB->Move(normal * depth / 2.0f);
                        }
                    

                }
            }
        }   

        void Draw(sf::RenderWindow& window) override
        {   
            for(Body* body : bodyList) body->Draw(window);
        }
};

int main()
{
    Game game;
    game.Construct(800, 600);
    game.Start();
}
