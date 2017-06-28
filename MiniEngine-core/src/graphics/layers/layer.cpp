#include "layer.h"

namespace MiniEngine
{
	namespace graphics
	{
		Layer::Layer(Renderer2D* renderer, Shader* shader, maths::mat4 projectionMatrix)
			: m_pRenderer(renderer), m_pShader(shader), m_projectionMatrix(projectionMatrix)
		{
			m_pShader->enable();
			//构造时设定投影矩阵，不用每一帧重新渲染
			m_pShader->setUniformMat4("projectionMatrix",m_projectionMatrix);
			m_pShader->disable();
		}

		Layer::~Layer()
		{
			delete m_pRenderer;
			delete m_pShader;

			for (size_t i = 0; i < m_renderables.size(); ++i)
			{
				delete m_renderables[i];
			}
		}

		void Layer::add(Renderable2D* renderable)
		{
			m_renderables.push_back(renderable);
		}

		void Layer::render()
		{
			m_pShader->enable();

			m_pRenderer->begin();

			for (const Renderable2D* renderable : m_renderables)
			{
				renderable->submit(m_pRenderer);
			}

			m_pRenderer->end();
			m_pRenderer->flush();

		}
	}
}