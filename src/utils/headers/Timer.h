#pragma once

class Timer {
public:
    Timer(): time(0) { };

    void Update(float dt);
    void Restart();

    float Get() const;
private:
    float time;
};

inline void Timer::Update(float dt) {
    time += dt;
}

inline void Timer::Restart() {
    time = 0;
}

inline float Timer::Get() const {
    return time;
}