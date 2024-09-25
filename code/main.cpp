#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <random>

#include "sourcecode/plainengine/LinkedList.h"
#include "sourcecode/plainengine/PlainEngine.h"
#include "sourcecode/plainphysics/PlainPhysics.h"

using namespace plain;

sf::RenderWindow window(sf::VideoMode(800, 600), "PhysicsEngine");

float FPS = 60.0f;

LinkedList<Body*> bodyList;
int bodyC = 50;

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
        int shapeType = 1;

        plain::Body *body = NULL;

        int x = rand() % 800;
        int y = rand() % 600;
        int radius = rand() % 15 + 10;

        if(shapeType == plain::RectangleShape)
        {
            // body = new body::Rectangle(20.0f, 20.0f, Vector2D(x, y), 2.0f, 0.5f, sf::Color::White, sf::Color::White, false);
        }
        else if(shapeType == plain::CircleShape)
        {
            body = new body::Circle(radius, Vector2D(x, y), 2.0f, 0.5f, sf::Color::White, sf::Color::White, false);
        }

        if(body != NULL) bodyList.insert(body);
    }

    bodyList[0]->SetFillColor(sf::Color::Black);
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

        bodyList[0]->Move(velocity);
    }

    for(int i = 0; i < bodyList.length(); i++)
    {
        bodyList[i]->SetOutlineColor(sf::Color::White);
    }

    for(int i = 0; i < bodyList.length() - 1; i++)
    {
        Body *bodyA = bodyList[i];

        for(int j = i + 1; j < bodyList.length(); j++)
        {
            Body *bodyB = bodyList[j];

            // if(collisions::IntersectPolygons(bodyA->GetTransformedVertices(), bodyB->GetTransformedVertices()))
            // {
            //     bodyA->SetOutlineColor(sf::Color::Red);
            //     bodyB->SetOutlineColor(sf::Color::Red);
            // }

            Vector2D normal; float depth;
            if(collisions::IntersectCircles(bodyA->position, bodyA->radius, bodyB->position, bodyB->radius, normal, depth))
            {
                bodyA->SetOutlineColor(sf::Color::Red);
                bodyB->SetOutlineColor(sf::Color::Red);
                bodyA->Move((normal * -1.0f) * depth / 2.0f);
                bodyB->Move(normal * depth / 2.0f);
            }
        }
    }

    for(int i = 0; i < bodyList.length(); i++)
        bodyList[i]->Rotate(45 * delta);
}

void Draw()
{
    // DrawThings

    window.clear(sf::Color::Black);

    for(int i = 0; i < bodyC; i++)
        if(bodyList[i] != NULL) 
            bodyList[i]->Draw(window);

    window.display();
}