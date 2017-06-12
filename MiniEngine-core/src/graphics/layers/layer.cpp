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

			for (int i = 0; i < m_Renderables.size(); ++i)
			{
				delete m_Renderables[i];
			}
		}

		void Layer::add(Renderable2D* renderable)
		{
			m_Renderables.push_back(renderable);
		}

		void Layer::render()
		{
			m_pShader->enable();

			m_pRenderer->begin();
			//移动整个图层
//			m_pRenderer->push(maths::mat4::translate(maths::vec3(5.0f, 5.0f, 0.0f)));
			for (const Renderable2D* renderable : m_Renderables)
			{
				m_pRenderer->submit(renderable);
			}
//			m_pRenderer->pop();
			m_pRenderer->end();
			m_pRenderer->flush();

		}
	}
}