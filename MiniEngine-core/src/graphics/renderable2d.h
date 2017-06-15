#pragma once

#include "buffers/buffer.h"
#include "buffers/indexBuffer.h"
#include "buffers/vertexArray.h"
#include "shaders.h"
#include "renderer2d.h"

#include "../maths/vec2.h"
#include "../maths/vec3.h"
#include "../maths/vec4.h"

namespace MiniEngine
{
	namespace graphics
	{
		struct VertexData
		{
			maths::vec3 vertex;
			maths::vec2 uv;//texture coordinate
			unsigned int color;
		};

		class Renderable2D
		{
		private:
			maths::vec3 m_position;
			maths::vec2 m_size;//Í¼Ôª´óÐ¡
			maths::vec4 m_color;
			std::vector<maths::vec2> m_uv;
		protected:
			Renderable2D() { setUVDefaults(); }
		public:
			Renderable2D(maths::vec3 position, maths::vec2 size, maths::vec4 color)
				: m_position(position), m_size(size), m_color(color)
			{ 
				setUVDefaults();
			}

			virtual ~Renderable2D() { }

			virtual void submit(Renderer2D* renderer) const
			{
				renderer->submit(this);
			}

			inline const maths::vec3& getPosition() const { return m_position; }
			inline const maths::vec2& getSize() const { return m_size; }
			inline const maths::vec4& getColor() const { return m_color; }
			inline const std::vector<maths::vec2>& getUV() const { return m_uv; }
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