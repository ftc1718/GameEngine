#pragma once

#include "renderable2d.h"

namespace MiniEngine
{
	namespace graphics
	{
		class Label : public Renderable2D
		{
		private:
			std::string m_text;
		public:
			Label(const std::string& text, float x, float y, maths::vec4 color);
			void submit(Renderer2D* renderer) const override;
		};
	}
}