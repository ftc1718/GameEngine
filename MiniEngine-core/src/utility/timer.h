#pragma once

#define WINDOWS_TIMER 1

#if WINDOWS_TIMER
#include <Windows.h>
#else
#include <chrono>
#endif

namespace MiniEngine {

#if WINDOWS_TIMER
	//游戏引擎架构p291
	class Timer
	{
	private:
		LARGE_INTEGER m_start;
		double m_frequency;
	public:
		Timer()
		{
			LARGE_INTEGER frequency;
			QueryPerformanceFrequency(&frequency);
			m_frequency = 1.0f / frequency.QuadPart;
			QueryPerformanceCounter(&m_start);
		}

		void reset()
		{
			QueryPerformanceCounter(&m_start);
		}

		double elapsed()//绘制一帧所需精确时间
		{
			LARGE_INTEGER current;
			QueryPerformanceCounter(&current);

			return (current.QuadPart - m_start.QuadPart) * m_frequency;
		}
	};
#else
	class Timer
	{
	private:
		typedef std::chrono::high_resolution_clock hrClock;
		typedef std::chrono::duration<float, std::milli> milliseconds_type;
		std::chrono::time_point<hrClock> m_Start;
	public:
		Timer()
		{
			reset();
		}

		void reset()
		{
			m_Start = hrClock::now();
		}

		float elapsed()
		{
			return std::chrono::duration_cast<milliseconds_type>(hrClock::now() - m_Start).count() / 1000.0f;
		}

	};
#endif
}