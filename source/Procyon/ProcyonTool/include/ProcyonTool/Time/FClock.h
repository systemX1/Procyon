#pragma once

#ifndef PRUTIL_FCLOCK_H
#define PRUTIL_FCLOCK_H

#include <chrono>

namespace PrUtil::Time {
    class FClock {
    public:
        explicit FClock() = default;

		/**
        * Update the clock
        */
		void Update();

		/**
		* Return the actual framerate (Depend on the delta time)
		*/
        [[nodiscard]] float GetFrameRate() const;

		/**
		* Return the actual delta time (Scale applied)
		*/
		[[nodiscard]] float GetDeltaTime() const;

		/**
		* Return the actual delta time (Scale not applied)
		*/
        [[nodiscard]] float GetUnscaledDeltaTime() const;

		/**
		* Return the time elapsed since clock creation
		*/
        [[nodiscard]] float GetTimeSinceStart() const;

		/**
		* Return the current timescale
		*/
        [[nodiscard]] float GetTimeScale() const;

		/**
		* Multiply the timescale by the given coefficient
		* @param p_coefficient
		*/
		void Scale(float p_coefficient);

		/**
		* Define a timescaleFactor
		* @param p_timeScaleFactor
		*/
		void SetTimeScaleFactor(float p_timeScaleFactor);

    private:
        void Init();

        std::chrono::steady_clock::time_point        m_startTime;
        std::chrono::steady_clock::time_point        m_lastTime;
        std::chrono::steady_clock::time_point        m_currTime;
        std::chrono::duration<double, std::ratio<1>> m_elapsedTime{};

        bool  m_inited         = false;
        float m_scaleFactor    = 1.0f;
        float m_deltaTime      = 0.0f;
        float m_timeSinceStart = 0.0f;
    };

}

#endif

