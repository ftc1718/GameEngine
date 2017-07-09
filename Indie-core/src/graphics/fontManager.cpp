#include "fontManager.h"

namespace Indie
{
	namespace graphics
	{
		std::vector<Font*> FontManager::m_fontsVector;

		void FontManager::add(Font* font)
		{
			m_fontsVector.push_back(font);
		}

		Indie::graphics::Font* FontManager::get()
		{
			return m_fontsVector[0];
		}

		Font* FontManager::get(const std::string& name)
		{
			for (Font* font : m_fontsVector)
			{
				if (font->getFontName() == name)
				{
					return font;
				}
			}
			return nullptr;//return a default font in label
		}


		Font* FontManager::get(const std::string& name, unsigned int size)
		{
			for (Font* font : m_fontsVector)
			{
				if (font->getSize() == size && font->getFontName() == name)
				{
					return font;
				}
			}
			return nullptr;//return a default font in label
		}

		void FontManager::clean()
		{
			for (int i = 0; i != m_fontsVector.size(); ++i)
			{
				delete m_fontsVector[i];
			}
		}
	}
}