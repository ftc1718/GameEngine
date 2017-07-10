#pragma once

#include "renderable2d.h"
#include "fontManager.h"

namespace indie
{
	namespace graphics
	{
		class Label : public Renderable2D
		{
		public:
			Font* m_pFont;
			std::string m_text;
		public:
			Label(const std::string& text, float x, float y, unsigned int color);//use default font
			Label(const std::string& text, float x, float y, Font* font, unsigned int color);
			Label(const std::string& text, float x, float y, const std::string& fontName, unsigned int color);
			Label(const std::string& text, float x, float y, const std::string& fontName, unsigned int size, unsigned int color);
			void submit(Renderer2D* renderer) const override;
			void validateFont(const std::string& fontName, unsigned int size = 0);
		};
	}
}