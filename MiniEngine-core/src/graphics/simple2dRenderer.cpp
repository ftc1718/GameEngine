#include "simple2dRenderer.h"

namespace MiniEngine
{
	namespace graphics
	{
		void Simple2DRenderer::submit(const Renderable2D* renderable2d)
		{
			m_renderQueue.push_back((StaticSprite*)renderable2d);
		}

		void Simple2DRenderer::flush()
		{
			while (!m_renderQueue.empty())
			{
				const StaticSprite* sprite = m_renderQueue.front();
				sprite->getVertexAarray()->bind();
				sprite->getIndexBuffer()->bind();

				sprite->getShader().setUniformMat4("modelMatrix", maths::mat4::translate(sprite->getPosition()));
				glDrawElements(GL_TRIANGLES, sprite->getIndexBuffer()->getIndexCnt(), GL_UNSIGNED_SHORT, 0);

				sprite->getVertexAarray()->unbind();
				sprite->getIndexBuffer()->unbind();

				m_renderQueue.pop_front();
			}
		}
	}
}