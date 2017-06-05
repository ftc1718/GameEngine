#pragma once

#include <deque>

#include "renderer2d.h"

namespace MiniEngine
{
	namespace graphics
	{
		class Simple2DRenderer : public Renderer2D
		{
		private:
			std::deque<const Renderable2D*> m_renderQueue;
		public:
			void submit(const Renderable2D* renderable2d) override;
			void flush() override;
		};
	}
}