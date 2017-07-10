#include "vertexArray.h"

namespace indie
{
	namespace graphics
	{
		VertexArray::VertexArray()
		{
			glGenVertexArrays(1, &m_arrayID);
		}
		VertexArray::~VertexArray()
		{
			glDeleteVertexArrays(1, &m_arrayID);

			for (size_t i = 0; i < m_buffers.size(); ++i)
			{
				delete m_buffers[i];
			}
		}

		//index表示属性的索引
		void VertexArray::addBuffer(Buffer* buffer, GLuint index)
		{
			bind();
			buffer->bind();

			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, buffer->getComponentCnt(), GL_FLOAT, GL_FALSE, 0, 0);

			buffer->unbind();
			unbind();

			m_buffers.push_back(buffer);
		}

		void VertexArray::bind() const
		{
			glBindVertexArray(m_arrayID);
		}

		void VertexArray::unbind() const
		{
			glBindVertexArray(0);
		}

	}
}