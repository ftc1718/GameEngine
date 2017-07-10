#include "indexBuffer.h"

namespace indie
{
	namespace graphics
	{
		//size��ʾdata�Ĵ�С�����鳤��,����������
		IndexBuffer::IndexBuffer(GLushort* data, GLsizei size)
			: m_indexCnt(size)
		{
			glGenBuffers(1, &m_bufferID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(GLushort), data, GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		IndexBuffer::IndexBuffer(GLuint* data, GLsizei size)
			: m_indexCnt(size)
		{
			glGenBuffers(1, &m_bufferID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(GLuint), data, GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		IndexBuffer::~IndexBuffer()
		{
			glDeleteBuffers(1, &m_bufferID);
		}

		void IndexBuffer::bind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
		}

		void IndexBuffer::unbind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

	}
}