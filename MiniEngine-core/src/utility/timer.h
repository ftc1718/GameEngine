#pragma once

#include <Windows.h>

namespace MiniEngine
{
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

		double elasped()//绘制一帧所需精确时间
		{
			LARGE_INTEGER current;
			QueryPerformanceCounter(&current);

			return (current.QuadPart - m_start.QuadPart) * m_frequency;
		}
	};
}