#include "font.h"

namespace MiniEngine
{
	namespace graphics
	{
		/*Font::Font()
		{
			m_pFTAtlas = ftgl::texture_atlas_new(512, 512, 2);
			m_pFTFont = ftgl::texture_font_new_from_file(m_pFTAtlas, 32, "arial.ttf");
		}*/

		Font::Font(std::string fontName, std::string fileName, unsigned int size)
			: m_fontName(fontName), m_fileName(fileName), m_size(size)
		{
			m_pFTAtlas = ftgl::texture_atlas_new(512, 512, 2);
			m_pFTFont = ftgl::texture_font_new_from_file(m_pFTAtlas, size, fileName.c_str());
		}
	}
}