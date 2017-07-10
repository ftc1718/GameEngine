#pragma once

#include <GL/glew.h>
namespace indie
{
	namespace graphics
	{
		//��������
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