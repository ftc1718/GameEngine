#pragma once

#include <string>
#include <FreeImage.h>

#ifdef INDIE_EMSCRIPTEN
	#define GLFW_INCLUDE_ES3
	#include <GLFW/glfw3.h>
#else
	#include <GL/glew.h>
#endif

#include "../utility/fileUtils.h"

namespace indie
{
	namespace graphics
	{
		class Texture
		{
		private:
			std::string m_fileName;
			std::string m_name;
			GLuint m_tID; //texture id
			GLsizei m_width;
			GLsizei m_height;
			unsigned int m_bitsPerPixel;
		public:
			Texture(const std::string& name, const std::string& fileName);
			~Texture();
			void bind() const;
			void unbind() const;

			//m_tID start from 1
			inline const GLuint getID() const { return m_tID; }
			inline const std::string& getTextureName() const { return m_name; }
			inline const GLsizei getWidth() const { return m_width; }
			inline const GLsizei getHeight() const { return m_height; }
		private:
			GLuint load();
		};
	}
}