#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>

#include "sourcecode\Plain\Plain.hpp"

sf::RenderWindow window(sf::VideoMode(800, 600), "Physics Engine");

int FPS = 60;

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
    // Start Things
}

void Update(float delta)
{
    // Update Things
}

void Draw()
{
    // DrawThings

    window.clear(sf::Color::White);
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
