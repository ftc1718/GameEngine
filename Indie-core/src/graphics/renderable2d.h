#pragma once

#include "buffers/buffer.h"
#include "buffers/indexBuffer.h"
#include "buffers/vertexArray.h"
#include "shaders.h"
#include "renderer2d.h"
#include "texture.h"

#include "../maths/vec2.h"
#include "../maths/vec3.h"
#include "../maths/vec4.h"

namespace indie
{
	namespace graphics
	{
		struct VertexData
		{
			maths::vec3 vertex;
			maths::vec2 uv;//texture coordinate
			float tid;
			unsigned int color;
		};

		class Renderable2D
		{
		protected:
			maths::vec3 m_position;
			maths::vec2 m_size;//Í¼Ôª´óÐ¡
			unsigned int m_color;
			std::vector<maths::vec2> m_uv;
			Texture* m_pTexture;
		protected:
			Renderable2D() : m_pTexture(nullptr) { setUVDefaults(); }
		public:
			Renderable2D(maths::vec3 position, maths::vec2 size, unsigned int color)
				: m_position(position), m_size(size), m_color(color), m_pTexture(nullptr)
			{ 
				setUVDefaults();
			}

			virtual ~Renderable2D() { }

			virtual void submit(Renderer2D* renderer) const
			{
				renderer->submit(this);
			}

			void setColor(unsigned int color) { m_color = color; }
			void setColor(const maths::vec4& color)
			{
				int r = color.x * 255.0f;
				int g = color.y * 255.0f;
				int b = color.z * 255.0f;
				int a = color.w * 255.0f;

				m_color = a << 24 | b << 16 | g << 8 | r;
			}

			inline const maths::vec3& getPosition() const { return m_position; }
			inline const void setPosition(const maths::vec3& position) { m_position = position; }
			inline const void setPosition(float x, float y) { m_position = maths::vec3(x, y, 0.0f); }

			inline const maths::vec2& getSize() const { return m_size; }
			inline const unsigned int getColor() const { return m_color; }
			inline const std::vector<maths::vec2>& getUV() const { return m_uv; }
			inline const GLuint gettID() const { return m_pTexture ? m_pTexture->getID() : 0; }
		private:
			void setUVDefaults()
			{
				m_uv.push_back(maths::vec2(0, 0));
				m_uv.push_back(maths::vec2(0, 1));
				m_uv.push_back(maths::vec2(1, 1));
				m_uv.push_back(maths::vec2(1, 0));
			}

		};
	}
}