#include "layer.h"

namespace indie
{
	namespace graphics
	{
		Layer::Layer(Renderer2D* renderer, Shader* shader, maths::mat4 projectionMatrix)
			: m_pRenderer(renderer), m_pShader(shader), m_projectionMatrix(projectionMatrix)
		{
			m_pShader->enable();
			//构造时设定投影矩阵，不用每一帧重新渲染
			m_pShader->setUniformMat4("projectionMatrix",m_projectionMatrix);

			GLint texIDs[] =
			{
				 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
				10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
				20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
				30, 31, 32
			};

			m_pShader->setUniform1iv("textures", texIDs, 32);
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