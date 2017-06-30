#include "staticSprite.h"

namespace MiniEngine
{
	namespace graphics
	{
		StaticSprite::StaticSprite(float x, float y, float width, float height, const maths::vec4& color, Shader& shader)
			:Renderable2D(maths::vec3(x, y, 0), maths::vec2(width, height), 0xffff00ff), m_shader(shader)
		{
			m_pVertexArray = new VertexArray();
			GLfloat vertices[] = 
			{
				0, 0, 0,
				0, height, 0,
				width, height, 0,
				width, 0, 0
			};

			GLfloat colors[] =
			{
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w
			};

			m_pVertexArray->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
			m_pVertexArray->addBuffer(new Buffer(colors, 4 * 4, 4), 1);
			//delete Buffer in ~VertexArray()

			GLushort indices[] =
			{
				0, 1, 2,
				2, 3, 0
			};

			m_pIndexBuffer = new IndexBuffer(indices, 6);
		}

		StaticSprite::~StaticSprite()
		{
			delete m_pVertexArray;
			delete m_pIndexBuffer;
		}
	}
}