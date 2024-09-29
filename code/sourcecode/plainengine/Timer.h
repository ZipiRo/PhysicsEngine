#pragma once

namespace EngineUtils
{
    class Timer
    {
    public:

        static Timer* Instance();
        static void Relese();
        void Reset();
        float DeltaTime();
        void TimeScale(float t);
        float TimeScale();  
        void Tick();

    private:
        Timer();
        ~Timer();

    private:

        static Timer* sInstance;

        std::chrono::system_clock::time_point mStartTime;
        std::chrono::duration<float> mDeltaTime;
        float mTimeScale;
    };
}