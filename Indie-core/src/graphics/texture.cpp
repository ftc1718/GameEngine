#include "texture.h"

namespace Indie
{
	namespace graphics
	{
		Texture::Texture(const std::string& fileName)
			: m_fileName(fileName)
		{
			m_tID = load();
		}

		Texture::~Texture()
		{

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
			BYTE* pixels = utils::loadTexture(m_fileName.c_str(), &m_width, &m_height);

			GLuint result;
			glGenTextures(1, &result);
			glBindTexture(GL_TEXTURE_2D, result);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels);
			glBindTexture(GL_TEXTURE_2D, 0);

			delete[] pixels; //free memory in loadTexture
			return result;
		}
	}
}