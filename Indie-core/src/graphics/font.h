#pragma once

#include <string>
#include "../maths/vec2.h"
#include "../../ext/freetype-gl/freetype-gl.h"

namespace indie
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
			maths::vec2 m_scale;
		public:
			Font(const std::string& fontName, const std::string& fileName, unsigned int size);
			~Font();

			//the font scale with the projection matrix
			void setScale(float x, float y);
			inline ftgl::texture_font_t* getFTFont() const { return m_pFTFont; }

			inline const unsigned int getSize() const { return m_size; }
			inline const std::string& getFontName() const { return m_fontName; }
			inline const std::string& getFileName() const { return m_fileName; }
			inline const maths::vec2& getScale() const { return m_scale; }
			inline const unsigned int getID() const { return m_pFTAtlas->id; }
		};
	}
}