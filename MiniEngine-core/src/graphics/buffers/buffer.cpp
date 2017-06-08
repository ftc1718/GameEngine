#include "buffer.h"

namespace MiniEngine
{
	namespace graphics
	{
		//dataSize��ʾdata���鳤�ȣ�attriComp��ʾ�������Ե�������������㹹��һ�����ԣ�
		Buffer::Buffer(GLfloat* data, GLsizei dataSize, GLuint componentCnt)
			: m_componentCnt(componentCnt)
		{
			glGenBuffers(1, &m_bufferID);
			glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
			glBufferData(GL_ARRAY_BUFFER, dataSize * sizeof(GLfloat), data, GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		Buffer::~Buffer()
		{
			glDeleteBuffers(1, &m_bufferID);
		}

		void Buffer::bind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
		}

		void Buffer::unbind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

	}
}