#include "batchRenderer2d.h"

namespace MiniEngine
{
	namespace graphics
	{
		BatchRenderer2D::BatchRenderer2D()
		{
			init();
		}

		BatchRenderer2D::~BatchRenderer2D()
		{
			delete m_pIndexBufferObj;
			glDeleteBuffers(1, &m_vertexBufferObj);
		}

		void BatchRenderer2D::init()
		{
			glGenVertexArrays(1, &m_vertexArrayObj);
			glGenBuffers(1, &m_vertexBufferObj);
			
			glBindVertexArray(m_vertexArrayObj);
			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObj);
			glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

			glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
			glEnableVertexAttribArray(SHADER_UV_INDEX);
			glEnableVertexAttribArray(SHADER_COLOR_INDEX);

			glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
			glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::uv)));
			glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::color)));

			glBindBuffer(GL_ARRAY_BUFFER, 0);

			GLuint* indices = new GLuint [RENDERER_INDICES_SIZE];

			int offset = 0;
			for (int i = 0; i < RENDERER_INDICES_SIZE; i += 6)
			{
				indices[i] = offset + 0;
				indices[i + 1] = offset + 1;
				indices[i + 2] = offset + 2;

				indices[i + 3] = offset + 2;
				indices[i + 4] = offset + 3;
				indices[i + 5] = offset + 0;

				offset += 4;
			}

			m_pIndexBufferObj = new IndexBuffer(indices, RENDERER_INDICES_SIZE);

			glBindVertexArray(0);
		}
		//bigin end只在第一次submit时进行绑定
		void BatchRenderer2D::begin()
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObj);
			m_pBuffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}

		void BatchRenderer2D::submit(const Renderable2D* renderable2d)
		{
			const maths::vec3& position = renderable2d->getPosition();
			const maths::vec2& size = renderable2d->getSize();
			const maths::vec4& color = renderable2d->getColor();
			const std::vector<maths::vec2>& uv = renderable2d->getUV();

			int r = color.x * 255.0f;
			int g = color.y * 255.0f;
			int b = color.z * 255.0f;
			int a = color.w * 255.0f;

			unsigned int c = a << 24 | b << 16 | g << 8 | r;

			m_pBuffer->vertex = *m_transformationBack * position;
			m_pBuffer->uv = uv[0];
			m_pBuffer->color = c;
			++m_pBuffer;

			m_pBuffer->vertex = *m_transformationBack * maths::vec3(position.x, position.y + size.y, position.z);
			m_pBuffer->uv = uv[1];
			m_pBuffer->color = c;
			++m_pBuffer; 

			m_pBuffer->vertex = *m_transformationBack * maths::vec3(position.x + size.x, position.y + size.y, position.z);
			m_pBuffer->uv = uv[2];
			m_pBuffer->color = c;
			++m_pBuffer;

			m_pBuffer->vertex = *m_transformationBack * maths::vec3(position.x + size.x, position.y, position.z);
			m_pBuffer->uv = uv[3];
			m_pBuffer->color = c;
			++m_pBuffer;

			m_indexCnt += 6;//通过六个索引绘制一个矩形
		}

		void BatchRenderer2D::end()
		{
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0); 
		}

		void BatchRenderer2D::flush()
		{
			glBindVertexArray(m_vertexArrayObj);
			m_pIndexBufferObj->bind();

			glDrawElements(GL_TRIANGLES, m_indexCnt, GL_UNSIGNED_INT, 0);

			m_pIndexBufferObj->unbind();
			glBindVertexArray(0);

			m_indexCnt = 0;
		}
	}
}