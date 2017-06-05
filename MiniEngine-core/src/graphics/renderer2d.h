#pragma once

#include "renderable2d.h"

namespace MiniEngine
{
	namespace graphics
	{
		class Renderer2D
		{
		public:
			virtual void submit(const Renderable2D* renderable2d) = 0;
			virtual void flush() = 0;
		};
	}
}