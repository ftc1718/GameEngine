#include "group.h"

namespace indie
{
	namespace graphics
	{
		Group::Group(const maths::mat4& transform)
			: m_transformationMatrix(transform)
		{
		}

		Group::~Group()
		{
			for (int i = 0; i != m_renderables.size(); ++i)
			{
				delete m_renderables[i];
			}
		}

		void Group::add(Renderable2D* renderable)
		{
			m_renderables.push_back(renderable);
		}

		void Group::submit(Renderer2D* renderer) const
		{
			renderer->push(m_transformationMatrix);

			for (const Renderable2D* renderable : m_renderables)
			{
				renderable->submit(renderer);
			}

			renderer->pop();
		}
	}
}