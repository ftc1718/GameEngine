#include "simple2dRenderer.h"

namespace MiniEngine
{
	namespace graphics
	{
		void Simple2DRenderer::submit(const Renderable2D* renderable2d)
		{
			m_renderQueue.push_back(renderable2d);
		}

		void Simple2DRenderer::flush()
		{
			while (!m_renderQueue.empty())
			{
				const Renderable2D* renderable2d = m_renderQueue.front();
				renderable2d->getVertexAarray()->bind();
				renderable2d->getIndexBuffer()->bind();

				renderable2d->getShader().setUniformMat4("modelMatrix", maths::mat4::translate(renderable2d->getPosition()));
				glDrawElements(GL_TRIANGLES, renderable2d->getIndexBuffer()->getIndexCnt(), GL_UNSIGNED_SHORT, 0);

				renderable2d->getVertexAarray()->unbind();
				renderable2d->getIndexBuffer()->unbind();

				m_renderQueue.pop_front();
			}
		}
	}
}