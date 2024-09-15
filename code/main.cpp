#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>

#include "sourcecode\Vector2D.h"

sf::RenderWindow window(sf::VideoMode(800, 600), "Physics Engine");

int FPS = 120;

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
            std::cout << "MaxFramesPerSecond: " << 1 / drawTime << " FPS" << '\n';
            std::cout << "DrawTime: " << drawTime * 1000.0f << " ms" << '\n';
            std::cout << "FramesPerSecond: " << frameCount << " FPS" << '\n';
            std::cout << std::endl;
            frameCount = 0;
            fpsTimer = fpsCurrentTime;
        }
    }

    return 0;
}

void Start()
{
    sf::Vector2f a;
    Plain::Vector2D b = Plain::Vector2D(10, 10);
    a = Plain::Vector2DtosfmlVector2D(b);

    std::cout << 'x' << a.x << ' ' << 'y' << a.y;
    // Start Things
}

void Update(float delta)
{
    // Update Things
}

void Draw()
{
    // DrawThings

    window.clear();
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
