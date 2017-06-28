#pragma once

#include "../renderable2d.h"
#include "../renderer2d.h"

namespace MiniEngine
{
	namespace graphics
	{
		class Group : public Renderable2D
		{
		private:
			std::vector<Renderable2D*> m_renderables;
			maths::mat4 m_transformationMatrix;
		public:
			Group(const maths::mat4& transform);
			~Group();
			void add(Renderable2D* renderable);
			void submit(Renderer2D* renderer) const override;
		};
	}
}