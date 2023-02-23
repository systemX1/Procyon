#include "ProcyonTool/Time/FClock.h"

void PrUtil::Time::FClock::Update() {
    m_lastTime = m_currTime;
    m_currTime = std::chrono::steady_clock::now();
    m_elapsedTime = m_currTime - m_lastTime;

    if(m_inited) {
        m_deltaTime = m_elapsedTime.count() > 0.1
                    ? 0.1f
                    : static_cast<float>(m_elapsedTime.count());
    } else {
        Init();
    }
}

float PrUtil::Time::FClock::GetFrameRate() const {
    return 1 / m_deltaTime;
}

float PrUtil::Time::FClock::GetDeltaTime() const {
    return m_deltaTime * m_scaleFactor;
}

float PrUtil::Time::FClock::GetUnscaledDeltaTime() const {
    return m_deltaTime;
}

float PrUtil::Time::FClock::GetTimeSinceStart() const {
    return m_timeSinceStart;
}

float PrUtil::Time::FClock::GetTimeScale() const {
    return m_scaleFactor;
}

void PrUtil::Time::FClock::Scale(float p_coefficient) {
    m_scaleFactor *= p_coefficient;
}

void PrUtil::Time::FClock::SetTimeScaleFactor(const float p_timeScaleFactor) {
    m_scaleFactor = p_timeScaleFactor;
}

void PrUtil::Time::FClock::Init() {
    m_inited= true;
    m_startTime = std::chrono::steady_clock::now();
    m_deltaTime = 0.0f;
    m_currTime = m_startTime;
    m_lastTime = m_startTime;
}
