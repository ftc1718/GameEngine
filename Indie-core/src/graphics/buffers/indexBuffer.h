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
		//±£´æË÷Òý
		class IndexBuffer
		{
		private:
			GLuint m_bufferID;
			GLuint m_indexCnt;
		public:
			IndexBuffer(GLushort* data, GLsizei size);
			IndexBuffer(GLuint* data, GLsizei size);
			~IndexBuffer();

			void bind() const;
			void unbind() const;

			inline GLuint getIndexCnt() const
			{
				return m_indexCnt;
			}
		};
	}
}