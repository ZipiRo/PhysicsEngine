namespace PlainEngine 
{
    class Engine
    {
    private:
        int width;
        int height;
        
        sf::RenderWindow *Window;

        EngineUtils::Timer* timer;
    public:
        virtual void Create() = 0;
        virtual void Update(float) = 0;
        virtual void Draw(sf::RenderWindow& window) = 0;

        void Construct(int width, int height);
        void Start();

        int GetWindowWidth();
        int GetWindowHeigth();

        float maxFps = 60.0F;
        std::string w_Name = "window";
        sf::Color w_BackgroundColor = sf::Color::Black;
        float viewZoomFactor = 1.0f;

        sf::Event *Event;
        sf::View *ViewPort;

        sf::Vector2i mouseLocalPos;
        sf::Vector2f mouseWorldPos;
    };
}