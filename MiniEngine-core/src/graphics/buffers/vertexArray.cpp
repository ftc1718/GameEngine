#include "vertexArray.h"

namespace MiniEngine
{
	namespace graphics
	{
		VertexArray::VertexArray()
		{
			glGenVertexArrays(1, &m_arrayID);
		}

		//index表示属性的suoyin
		void VertexArray::addBuffer(Buffer* buffer, GLuint index)
		{
			bind();
			buffer->bind();

			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, buffer->getComponentCnt(), GL_FLOAT, GL_FALSE, 0, 0);

			buffer->unbind();
			unbind();
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