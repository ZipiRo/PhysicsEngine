#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <random>
#include <list>

#include "sourcecode/plainengine/PlainEngine.h"
#include "sourcecode/plainphysics/PlainPhysics.h"

using namespace plain;

sf::RenderWindow window(sf::VideoMode(800, 600), "PhysicsEngine");

float FPS = 61.0f;

std::list<Body*> bodyList;
int bodyC = 5;

void Start();
void Update(float delta);
void Draw();

int main()
{
    EngineUtils::Timer* timer = EngineUtils::Timer::Instance();

    float elapsedTime = 0.0f;
    int frames = 0;

    Start();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Escape)
                    window.close();
            }
        }
        
        timer->Tick();

        if(timer->DeltaTime() >= 1.0 / FPS)
        {   
            timer->Reset();
            elapsedTime += timer->DeltaTime();
            frames++;

            if(elapsedTime >= 1.0f){
                std::cout << (int)(1 / timer->DeltaTime()) << "fps" << '\n';
                elapsedTime = 0.0f ;
                frames = 0;
            }

            Update(timer->DeltaTime()); 
        }

        Draw();
    }

    EngineUtils::Timer::Relese();

    return 0;
}

void Start()
{
    // Initialize Things

    srand(time(0));
 
    for(int i = 0; i < bodyC; i++)
    {
        int shapeType = plain::RectangleShape;

        plain::Body *body;

        int x = rand() % 800;
        int y = rand() % 600;
        int radius = rand() % 15 + 10;

        if(shapeType == plain::RectangleShape)
        {
            body = new body::Rectangle(25.0f, 25.0f, Vector2D(x, y), 2.0f, 0.5f, sf::Color::White, sf::Color::White, false);
        }
        else if(shapeType == plain::CircleShape)
        {
            body = new body::Circle(radius, Vector2D(x, y), 2.0f, 0.5f, sf::Color::White, sf::Color::White, false);
        }

        bodyList.push_back(body);
    }

    bodyList.front()->SetFillColor(sf::Color::Transparent);
}

void Update(float delta)
{
    // Update Things

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
        plain::Vector2D velocity = direction * 200.0f * delta;

        bodyList.front()->Move(velocity);
    }

    for(Body* body : bodyList)
    {
        body->SetOutlineColor(sf::Color::White);
        body->Rotate(-45 * delta);
    }

    for(auto body_it = bodyList.begin(), body_it_ = body_it; body_it != --bodyList.end(); ++body_it)
    {
        Body* bodyA = *(body_it);    

        for(auto body_jt = ++body_it_; body_jt != bodyList.end(); ++body_jt)
        {
            Body* bodyB = *(body_jt);

            Vector2D normal; float depth;
            
            if(collisions::IntersectPolygons(bodyA->GetTransformedVertices(), bodyB->GetTransformedVertices(), normal, depth))
            {
                if(vectormath::NAN_Values(normal)) continue;
                bodyA->SetOutlineColor(sf::Color::Red);
                bodyB->SetOutlineColor(sf::Color::Red);
                bodyA->Move((normal * -1.0f) * depth / 2.0f);
                bodyB->Move(normal * depth / 2.0f);
            }

            // if(collisions::IntersectCircles(bodyA->position, bodyA->radius, bodyB->position, bodyB->radius, normal, depth))
            // {
            //     if(vectormath::NAN_Values(normal)) continue;
            //     bodyA->SetOutlineColor(sf::Color::Red);
            //     bodyB->SetOutlineColor(sf::Color::Red);
            //     bodyA->Move((normal * -1.0f) * depth / 2.0f);
            //     bodyB->Move(normal * depth / 2.0f);
            // }
        }
    }
}

void Draw()
{
    // DrawThings

    window.clear(sf::Color::Black);

    for(Body* body : bodyList)
            body->Draw(window);

    window.display();
}