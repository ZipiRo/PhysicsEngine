namespace PlainEngine 
{
    class Engine
    {
    private:
        int width;
        int height;
        float timeScale;
        
        sf::RenderWindow *window;

        EngineUtils::Timer* timer;
    public:
        virtual void Create() = 0;
        virtual void Update(float) = 0;
        virtual void Draw(sf::RenderWindow& window) = 0;

        void Construct(int width, int heigth);
        void Start();

        int GetWindowWidth();
        int GetWindowHeigth();

        float maxFps;
        std::string w_Name;
        sf::Color w_BackgroundColor;

        sf::Event *event;
        sf::View *viewport;

        sf::Vector2i mouseLocalPos;
        sf::Vector2f mouseWorldPos;
    };
}