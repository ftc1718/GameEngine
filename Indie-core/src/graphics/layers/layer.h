#pragma once

#include <vector>

#include "../renderable2d.h"
#include "../renderer2d.h"

namespace indie
{
	namespace graphics
	{
		class Layer
		{
		private:
			Renderer2D* m_pRenderer;
			Shader* m_pShader;
			std::vector<Renderable2D*> m_renderables;
			maths::mat4 m_projectionMatrix;
		public:
			Layer(Renderer2D* renderer, Shader* shader, maths::mat4 projectionMatrix);
			virtual ~Layer();
			virtual void add(Renderable2D* renderable);
			virtual void render();

			inline const std::vector<Renderable2D*>& getRenderables() const { return m_renderables; }
		};

	}
}