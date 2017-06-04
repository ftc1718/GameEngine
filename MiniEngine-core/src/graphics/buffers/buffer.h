#pragma once

#include <GL/glew.h>
namespace MiniEngine
{
	namespace graphics
	{
		//��������
		class Buffer
		{
		private:
			GLuint m_bufferID;
			GLuint m_componentCnt;
		public:
			Buffer(GLfloat* data, GLsizei size, GLuint componentCnt);

			void bind() const;
			void unbind() const;

			inline GLuint getComponentCnt() const
			{
				return m_componentCnt;
			}
		};
	}
}