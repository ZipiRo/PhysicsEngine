namespace PlainEngine 
{
    class Engine
    {
    private:
        int width;
        int heigth;
        float timeScale;
        
        sf::RenderWindow* window;
        sf::Event* event;
        EngineUtils::Timer* timer;
        
    public:
        virtual void Create() = 0;
        virtual void Update(float) = 0;
        virtual void Draw(sf::RenderWindow& window) = 0;

        void Construct(int width, int heigth);
        void Start();

        int GetWidth();
        int GetHeigth();

        float maxFps;
        std::string w_Name;
        sf::Color w_BackgroundColor;
    };
}