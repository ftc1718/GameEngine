#pragma once

#include "renderable2d.h"

namespace MiniEngine
{
	namespace graphics
	{
		class StaticSprite : public Renderable2D
		{
		private:
			VertexArray* m_pVertexArray;
			IndexBuffer* m_pIndexBuffer;
			Shader& m_shader;
		public:
			StaticSprite(float x, float y, float width, float height, const maths::vec4& color, Shader& shader);
			~StaticSprite();

			inline Shader& getShader() const { return m_shader; }
			inline const VertexArray* getVertexAarray() const { return m_pVertexArray; }
			inline const IndexBuffer* getIndexBuffer() const { return m_pIndexBuffer; }
		};
	}
}