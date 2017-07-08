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
			glEnableVertexAttribArray(SHADER_TID_INDEX);
			glEnableVertexAttribArray(SHADER_COLOR_INDEX);

			glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
			glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::uv)));
			glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::tid)));
			glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::color)));

			glBindBuffer(GL_ARRAY_BUFFER, 0);

			GLuint* indices = new GLuint[RENDERER_INDICES_SIZE];

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
			const unsigned int color = renderable2d->getColor();
			const std::vector<maths::vec2>& uv = renderable2d->getUV();
			//tid == 0 not to use texture
			const GLuint tid = renderable2d->gettID();

			//texSlot == -1 means do not use texture
			float texSlot = -1.0f;

			if (tid > 0)
			{
				bool found = false;
				for (int i = 0; i != m_textureSlots.size(); ++i)
				{
					if (m_textureSlots[i] == tid)
					{
						texSlot = (float)i;
						found = true;
						break;
					}
				}

				if (!found)
				{
					if (m_textureSlots.size() >= RENDERER_MAX_TEXTURES)
					{
						end();
						flush();
						begin();
						m_textureSlots.clear();
					}
					m_textureSlots.push_back(tid);
					texSlot = (float)(m_textureSlots.size() - 1);
				}
			}

			m_pBuffer->vertex = *m_transformationBack * position;
			m_pBuffer->uv = uv[0];
			m_pBuffer->tid = texSlot;
			m_pBuffer->color = color;
			++m_pBuffer;

			m_pBuffer->vertex = *m_transformationBack * maths::vec3(position.x, position.y + size.y, position.z);
			m_pBuffer->uv = uv[1];
			m_pBuffer->tid = texSlot;
			m_pBuffer->color = color;
			++m_pBuffer;

			m_pBuffer->vertex = *m_transformationBack * maths::vec3(position.x + size.x, position.y + size.y, position.z);
			m_pBuffer->uv = uv[2];
			m_pBuffer->tid = texSlot;
			m_pBuffer->color = color;
			++m_pBuffer;

			m_pBuffer->vertex = *m_transformationBack * maths::vec3(position.x + size.x, position.y, position.z);
			m_pBuffer->uv = uv[3];
			m_pBuffer->tid = texSlot;
			m_pBuffer->color = color;
			++m_pBuffer;

			m_indexCnt += 6;//通过六个索引绘制一个矩形
		}

		void BatchRenderer2D::drawString(const std::string& text, const maths::vec3& position, const Font& font, unsigned int color)
		{
			using namespace ftgl;

			float texSlot = -1.0f;
			bool found = false;
			for (int i = 0; i != m_textureSlots.size(); ++i)
			{
				if (m_textureSlots[i] == font.getID())
				{
					texSlot = (float)i;
					found = true;
					break;
				}
			}

			if (!found)
			{
				if (m_textureSlots.size() >= RENDERER_MAX_TEXTURES)
				{
					end();
					flush();
					begin();
					m_textureSlots.clear();
				}
				m_textureSlots.push_back(font.getID());
				texSlot = (float)(m_textureSlots.size() - 1);
			}

			float scaleX = 960.0f / 32.0f;
			float scaleY = 540.0f / 18.0f;

			float x = position.x;

			for (int i = 0; i != text.length(); ++i)
			{
				char c = text[i];
				texture_glyph_t* glyph = texture_font_get_glyph(font.getFTFont(), c);
				if (glyph)
				{
					if (i > 0)
					{
						float kerning = texture_glyph_get_kerning(glyph, text[i - 1]);
						x += kerning / scaleX;
					}
					float x0 = x + glyph->offset_x / scaleX;
					float y0 = position.y + glyph->offset_y / scaleY;
					float x1 = x0 + glyph->width / scaleX;
					float y1 = y0 - glyph->height / scaleY;

					float u0 = glyph->s0;
					float v0 = glyph->t0;
					float u1 = glyph->s1;
					float v1 = glyph->t1;

					m_pBuffer->vertex = *m_transformationBack * maths::vec3(x0, y0, 0.0f);
					m_pBuffer->uv = maths::vec2(u0, v0);
					m_pBuffer->tid = texSlot;
					m_pBuffer->color = color;
					++m_pBuffer;

					m_pBuffer->vertex = *m_transformationBack * maths::vec3(x0, y1, 0.0f);
					m_pBuffer->uv = maths::vec2(u0, v1);
					m_pBuffer->tid = texSlot;
					m_pBuffer->color = color;
					++m_pBuffer;

					m_pBuffer->vertex = *m_transformationBack * maths::vec3(x1, y1, 0.0f);
					m_pBuffer->uv = maths::vec2(u1, v1);
					m_pBuffer->tid = texSlot;
					m_pBuffer->color = color;
					++m_pBuffer;

					m_pBuffer->vertex = *m_transformationBack * maths::vec3(x1, y0, 0.0f);
					m_pBuffer->uv = maths::vec2(u1, v0);
					m_pBuffer->tid = texSlot;
					m_pBuffer->color = color;
					++m_pBuffer;

					m_indexCnt += 6;

					x += glyph->advance_x / scaleX;
				}
			}
		}

		void BatchRenderer2D::end()
		{
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void BatchRenderer2D::flush()
		{
			for (int i = 0; i != m_textureSlots.size(); ++i)
			{
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, m_textureSlots[i]);
			}

			glBindVertexArray(m_vertexArrayObj);
			m_pIndexBufferObj->bind();

			glDrawElements(GL_TRIANGLES, m_indexCnt, GL_UNSIGNED_INT, 0);

			m_pIndexBufferObj->unbind();
			glBindVertexArray(0);

			m_indexCnt = 0;
		}
	}
}