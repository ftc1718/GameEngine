#include "font.h"

namespace Indie
{
	namespace graphics
	{
		Font::Font(const std::string& fontName, const std::string& fileName, unsigned int size)
			: m_fontName(fontName), m_fileName(fileName), m_size(size)
		{
			m_pFTAtlas = ftgl::texture_atlas_new(512, 512, 2);
			m_pFTFont = ftgl::texture_font_new_from_file(m_pFTAtlas, size, fileName.c_str());
		}

		Font::~Font()
		{
			ftgl::texture_font_delete(m_pFTFont);
			ftgl::texture_atlas_delete(m_pFTAtlas);
		}
	}
}