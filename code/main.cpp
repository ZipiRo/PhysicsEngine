#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <random>

#include "sourcecode/plain/Plain.hpp"
#include "sourcecode/game/Game.hpp"

sf::RenderWindow window(sf::VideoMode(800, 600), "Physics Engine");

int FPS = 60;

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
    srand(time(0));
 
    for(int i = 0; i < bodyC; i++)
    {
        int shapeType = i % 2;

        Plain::Body *body = NULL;

        int x = rand() % 700;
        int y = rand() % 500;

        if(shapeType == Plain::RectangleShape)
        {
            body = new Plain::Rectangle(20.0f, 20.0f, Plain::Vector2D(x, y), 2.0f, 0.5f, sf::Color::Blue, sf::Color::White, false);
        }
        else if(shapeType == Plain::CircleShape)
        {
            body = new Plain::Circle(10.0f, Plain::Vector2D(x, y), 2.0f, 0.5f, sf::Color::Blue, sf::Color::White, false);
        }

        if(body != NULL) bodyList.insert(body);
    }
}

void Update(float delta)
{
    // Update Things
    
    for(int i = 0; i < bodyC; i++)
        if(bodyList[i] != NULL) {
            bodyList[i]->Move(Plain::Vector2D(0.0f, 9.81f) * delta);
            bodyList[i]->Rotate(20.0f * delta);
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
