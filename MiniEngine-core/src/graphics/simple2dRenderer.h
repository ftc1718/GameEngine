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
			/*���ڻ�ɾ��simpleRenderer
			  ������Ҫʵ��bengin,end,drawString
			  ��Renderer2D�пɲ�ʵ��Ϊ���麯����
			  ʵ��Ϊ��ͨ�麯������
			*/
			void submit(const Renderable2D* renderable2d) override;
			void flush() override;
		};
	}
}