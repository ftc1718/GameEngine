#pragma once

#include <deque>

#include "renderer2d.h"
#include "renderable2d.h"
#include "staticSprite.h"

namespace MiniEngine
{
	namespace graphics
	{
		class Simple2DRenderer : public Renderer2D
		{
		private:
			std::deque<const StaticSprite*> m_renderQueue;
		public:
			/*后期会删除simpleRenderer
			  它不需要实现bengin,end,drawString
			  故Renderer2D中可不实现为纯虚函数，
			  实现为普通虚函数即可
			*/
			void submit(const Renderable2D* renderable2d) override;
			void flush() override;
		};
	}
}