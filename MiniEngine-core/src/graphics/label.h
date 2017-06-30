#pragma once

#include "renderable2d.h"

namespace MiniEngine
{
	namespace graphics
	{
		class Label : public Renderable2D
		{
		public:
			Font* m_pFont;
			std::string m_text;
		public:
			Label(const std::string& text, float x, float y, Font* font, unsigned int color);
			void submit(Renderer2D* renderer) const override;
		};
	}
}