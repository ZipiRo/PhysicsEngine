#pragma once

namespace EngineUtils
{
    class Timer
    {
    private:

        static Timer* sInstance;

        std::chrono::system_clock::time_point mStartTime;
        std::chrono::duration<float> mDeltaTime;
        float mTimeScale;

    public:

        static Timer* Instance();
        static void Relese();

        void Reset();

        float DeltaTime();

        void TimeScale(float t = 1.0f);

        float TimeScale();  

        void Tick();

    private:

        Timer();
        ~Timer();
    };
}