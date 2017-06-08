#include "buffer.h"

namespace MiniEngine
{
	namespace graphics
	{
		//dataSize表示data数组长度，attriComp表示顶点属性的组件数（几个点构成一个属性）
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