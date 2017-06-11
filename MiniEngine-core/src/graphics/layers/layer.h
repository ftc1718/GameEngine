#pragma once

#include <vector>

#include "../renderable2d.h"
#include "../renderer2d.h"

namespace MiniEngine
{
	namespace graphics
	{
		class Layer
		{
		private:
			Renderer2D* m_pRenderer;
			Shader* m_pShader;
			std::vector<Renderable2D*> m_Renderables;
			maths::mat4 m_projectionMatrix;
		protected:
			Layer(Renderer2D* renderer, Shader* shader, maths::mat4 projectionMatrix);
		public:
			virtual ~Layer();
			virtual void add(Renderable2D* renderable);
			virtual void render();
		};

	}
}