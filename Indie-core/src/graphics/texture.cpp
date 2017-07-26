#include "texture.h"
#include "../utility/log.h"
#include <iostream>

namespace indie
{
	namespace graphics
	{
		Texture::Texture(const std::string& name, const std::string& fileName)
			: m_name(name), m_fileName(fileName)
		{
			m_tID = load();
		}

		Texture::~Texture()
		{
			glDeleteTextures(1, &m_tID);
		}

		void Texture::bind() const
		{
			glBindTexture(GL_TEXTURE_2D, m_tID);
		}

		void Texture::unbind() const
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		GLuint Texture::load()
		{
			BYTE* pixels = utils::loadTexture(m_fileName.c_str(), &m_width, &m_height, &m_bitsPerPixel);

			GLuint result;
			glGenTextures(1, &result);
			glBindTexture(GL_TEXTURE_2D, result);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			if (m_bitsPerPixel != 24 && m_bitsPerPixel != 32)
			{
				INDIE_ERROR("[Texture] Unsupport image bit-depth! (%d)", m_bitsPerPixel);
			}

			GLint internalFormat = m_bitsPerPixel == 32 ? GL_RGBA : GL_RGB;
			GLenum format = m_bitsPerPixel == 32 ?
#ifdef INDIE_EMSCRIPTEN
			GL_RGBA : GL_RGB;
#else
			GL_BGRA: GL_BGR;
#endif
			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, pixels);
			glBindTexture(GL_TEXTURE_2D, 0);

			delete[] pixels; //free memory in loadTexture
			return result;
		}
	}
}