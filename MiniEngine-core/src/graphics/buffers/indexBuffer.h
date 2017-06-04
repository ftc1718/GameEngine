#pragma once

#include <GL/glew.h>
namespace MiniEngine
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

			void bind() const;
			void unbind() const;

			inline GLuint getIndexCnt() const
			{
				return m_indexCnt;
			}
		};
	}
}