#pragma once

#ifdef INDIE_EMSCRIPTEN
	#define GLFW_INCLUDE_ES3
	#include <GLFW/glfw3.h>
#else
	#include <GL/glew.h>
#endif

namespace indie
{
	namespace graphics
	{
		//±£´æÊý¾Ý
		class Buffer
		{
		private:
			GLuint m_bufferID;
			GLuint m_componentCnt;
		public:
			Buffer(GLfloat* data, GLsizei size, GLuint componentCnt);
			~Buffer();

			void bind() const;
			void unbind() const;

			inline GLuint getComponentCnt() const
			{
				return m_componentCnt;
			}
		};
	}
}