#pragma once

#include <string>
#include "../../ext/freetype-gl/freetype-gl.h"

namespace MiniEngine
{
	namespace graphics
	{
		class Font
		{
		private:
			ftgl::texture_atlas_t* m_pFTAtlas;
			ftgl::texture_font_t* m_pFTFont;

			unsigned int m_size;
			std::string m_fontName;
			std::string m_fileName;
		public:
//			Font(); //default font
			Font(std::string fontName, std::string fileName, unsigned int size);

			inline ftgl::texture_font_t* getFTFont() const { return m_pFTFont; }

			inline const unsigned int getSize() const { return m_size; }
			inline const std::string getFontName() const { return m_fontName; }
			inline const std::string getFileName() const { return m_fileName; }
			inline const unsigned int getID() const { return m_pFTAtlas->id; }
		};
	}
}