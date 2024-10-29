#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <chrono>

#include "Timer.h"
#include "Engine.h"

namespace PlainEngine
{
    void Engine::Initialize(int width, int height, std::string title)
    {   
        this->width = width;
        this->height = height;
        this->title = title;

        this->Window = new sf::RenderWindow(sf::VideoMode(this->width, this->height), this->title);
        this->ViewPort = new sf::View(sf::Vector2f(this->width / 2, this->height / 2), sf::Vector2f(this->width, this->height));
        this->Time = new EngineUtils::Timer(this->TimeScale);
        
        this->ViewPort->zoom(0.1f);
        this->Window->setView(*this->ViewPort);
    }

    void Engine::Run()
    {
        this->OnStart();

        sf::Event event;
        while (this->Window->isOpen())
        {
            while (this->Window->pollEvent(event))
            {
                if(event.type == sf::Event::Closed)
                {
                    this->Window->close();
                }
                
                if(event.type == sf::Event::KeyPressed){
                    if(event.key.code == sf::Keyboard::Escape)
                        this->Window->close();
                }
            }

            mouseLocalPos = sf::Mouse::getPosition(*this->Window);
            mouseWorldPos = this->Window->mapPixelToCoords(mouseLocalPos);

            this->Time->Tick();

            if(this->Time->DeltaTime() >= 1.0 / this->MaxFramesPerSecond)
            {
                this->Time->Reset();

                this->OnUpdate(this->Time->DeltaTime()); 
            }
            
            this->Window->clear();

            this->OnDraw(this->Window);

            this->Window->display();
        }
        
        delete this->Window;
        delete this->ViewPort;
        delete this->Time;

        this->OnQuit();
    }

    float Engine::WindowWidth() { return this->width; }
    float Engine::WindowHeight() { return this->height; }
}