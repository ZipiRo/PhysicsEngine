#pragma once

namespace EngineUtils
{
    class Timer
    {
    private:
        std::chrono::system_clock::time_point mStartTime;
        std::chrono::duration<float> mDeltaTime;
        float mTimeScale;

    public:
        Timer();
        Timer(float timeScale);
        void Reset();
        float DeltaTime();
        void TimeScale(float t);
        float TimeScale();  
        void Tick();
    };
}