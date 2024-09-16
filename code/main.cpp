#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <random>

#include "sourcecode/plain/Plain.hpp"
#include "sourcecode/game/Game.hpp"

sf::RenderWindow window(sf::VideoMode(800, 600), "Physics Engine");

int FPS = 120;

Plain::LinkedList<Plain::Body*> bodyList;
int bodyC = 10;

void Start();
void Update(float delta);
void Draw();
float GetDrawTime();

int main()
{
    std::chrono::high_resolution_clock::time_point lastTime = std::chrono::high_resolution_clock::now();
    float delta = 0.0f;
    float drawInterval = 1.0f / FPS;
    float accumulator = 0.0f;
    int frameCount = 0;
    auto fpsTimer = std::chrono::high_resolution_clock::now();

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

        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> elapsedTime = currentTime - lastTime;
        lastTime = currentTime;
        delta = elapsedTime.count();

        accumulator += delta;

        while (accumulator >= drawInterval)
        {
            Update(drawInterval);
            accumulator -= drawInterval;
            frameCount++;
        }

        float drawTime = GetDrawTime();

        auto fpsCurrentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> fpsElapsedTime = fpsCurrentTime - fpsTimer;
        if (fpsElapsedTime.count() >= 1.0f)
        {
            std::cout << "FramesPerSecond: " << (int)(1.0f / drawTime) << " fps" << '\n';
            std::cout << "DrawTime: " << drawTime * 1000.0f << " ms" << '\n';
            std::cout << std::endl;
            frameCount = 0;
            fpsTimer = fpsCurrentTime;
        }
    }

    return 0;
}

void Start()
{
    // Initialize Things

    srand(time(0));
 
    for(int i = 0; i < bodyC; i++)
    {
        int shapeType = 1;

        Plain::Body *body = NULL;

        int x = rand() % 700;
        int y = rand() % 500;

        if(shapeType == Plain::RectangleShape)
        {
            body = new Plain::Rectangle(20.0f, 20.0f, Plain::Vector2D(x, y), 2.0f, 0.5f, sf::Color::Blue, sf::Color::White, false);
        }
        else if(shapeType == Plain::CircleShape)
        {
            body = new Plain::Circle(20.0f, Plain::Vector2D(x, y), 2.0f, 0.5f, sf::Color::Blue, sf::Color::White, false);
        }

        if(body != NULL) bodyList.insert(body);
    }
}

void Update(float delta)
{
    // Update Things
    
    Plain::Vector2D direction;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        direction = Plain::Vector2D(0, -1);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        direction = Plain::Vector2D(0, 1);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        direction = Plain::Vector2D(-1, 0);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        direction = Plain::Vector2D(1, 0);

    if(direction.x != 0 || direction.y != 0)
    {
        direction = Plain::Normalize(direction);
        Plain::Vector2D velocity = direction * 200.0f * delta;

        bodyList[0]->Move(velocity);
    }

    for(int i = 0; i < bodyList.length() - 1; i++)
    {
        Plain::Body *bodyA = bodyList[i];

        for(int j = i + 1; j < bodyList.length(); j++)
        {
            Plain::Body *bodyB = bodyList[j];
            
            Plain::Vector2D normal; float depth;
            if(Plain::IntersectCircles(bodyA->position, bodyA->radius, bodyB->position, bodyB->radius, normal, depth))
            {
                bodyA->Move((normal * -1.0f) * depth / 2.0f);
                bodyB->Move(normal * depth / 2.0f);
            }
        }
    }
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

float GetDrawTime()
{
    auto start = std::chrono::high_resolution_clock::now();

    Draw();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> drawDuration = end - start;

    return drawDuration.count();
}