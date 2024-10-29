namespace PlainEngine 
{
    class Engine
    {
    private:

        std::string title;
        int width;
        int height;
        
        sf::RenderWindow *Window;
        sf::View *ViewPort;
        EngineUtils::Timer *Time;
    public:
        virtual void OnStart() = 0;
        virtual void OnUpdate(float time) = 0;
        virtual void OnDraw(sf::RenderWindow* window) = 0;
        virtual void OnQuit() = 0;

        void Initialize(int width, int height, std::string title);
        void Run();

        float WindowWidth();
        float WindowHeight();

        float MaxFramesPerSecond = 60.0F;
        float TimeScale = 1.0f;

        sf::Vector2i mouseLocalPos;
        sf::Vector2f mouseWorldPos;
    };
}