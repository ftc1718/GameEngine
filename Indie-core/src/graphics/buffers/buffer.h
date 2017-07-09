#pragma once

#include <GL/glew.h>
namespace Indie
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