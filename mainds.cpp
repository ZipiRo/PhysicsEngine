#include <PlainEngine.h>
#include <PlainPhysics.h>

using namespace PlainEngine;
using namespace PlainPhysics;

class Demo : public Engine
{
public:
    Demo()
    {
        TimeScale = 1.0f;
        MaxFramesPerSecond = 9999.0f;
    }
private:
    void OnStart() override 
    {
    }


    float elapsedTime;
    void OnUpdate(float delta) override
    {
        elapsedTime += delta;
        if(elapsedTime >= 1.0f){
            std::cout << "ElapsedTime " << elapsedTime << '\n';
            std::cout << 1 / delta << "FPS\n";
            elapsedTime = 0;
        }
    }


    void OnDraw(sf::RenderWindow* Window) override
    {
    }

    void OnQuit()
    {
    }
};

int main()
{

    Demo demo;
    demo.Initialize(400, 400, "GameEngine");
    demo.Run();

    return 0;
}