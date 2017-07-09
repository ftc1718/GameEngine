#include "label.h"

namespace Indie
{
	namespace graphics
	{
		Label::Label(const std::string& text, float x, float y, unsigned int color)
			: Renderable2D(maths::vec3(x, y, 0.0f), maths::vec2(), color), m_text(text), m_pFont(FontManager::get("Arial"))
		{

		}
		Label::Label(const std::string& text, float x, float y, Font* font, unsigned int color)
			: Renderable2D(maths::vec3(x, y, 0.0f), maths::vec2(), color), m_text(text), m_pFont(font)
		{

		}

		Label::Label(const std::string& text, float x, float y, const std::string& fontName, unsigned int color)
			: Renderable2D(maths::vec3(x, y, 0.0f), maths::vec2(), color), m_text(text), m_pFont(FontManager::get(fontName))
		{
			validateFont(fontName);
		}

		Label::Label(const std::string& text, float x, float y, const std::string& fontName, unsigned int size, unsigned int color)
			: Renderable2D(maths::vec3(x, y, 0.0f), maths::vec2(), color), m_text(text), m_pFont(FontManager::get(fontName, size))
		{
			validateFont(fontName, size);
		}

		void Label::submit(Renderer2D* renderer) const
		{
			renderer->drawString(m_text, m_position, *m_pFont, m_color);
		}

		void Label::validateFont(const std::string& fontName, unsigned int size)

		{
			if (m_pFont == nullptr)
			{
				std::cout << "NULL Font! Font = " << fontName;
				if (size > 0)
				{
					std::cout << " , Size = " << size;
				}
				std::cout << std::endl;

				m_pFont = FontManager::get("Arial");//default font
			}
		}

	}
}