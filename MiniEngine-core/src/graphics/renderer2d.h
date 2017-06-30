#pragma once

#include <vector>
#include "font.h"
#include "../maths/mat4.h"

namespace MiniEngine
{
	namespace graphics
	{
		class Renderable2D;

		class Renderer2D
		{
		protected:
			std::vector<maths::mat4> m_transformationMatrix;
			const maths::mat4* m_transformationBack;
		protected:
			Renderer2D()
			{
				m_transformationMatrix.push_back(maths::mat4::identity());
				m_transformationBack = &m_transformationMatrix.back();
			}

		public:
			void push(const maths::mat4& matrix)
			{
				//no override
				m_transformationMatrix.push_back(m_transformationMatrix.back() * matrix);
				m_transformationBack = &m_transformationMatrix.back();
			}
			
			void pop()
			{
				if (m_transformationMatrix.size() > 1)
				{
					m_transformationMatrix.pop_back();
				}
				m_transformationBack = &m_transformationMatrix.back();
			}
			
			virtual void begin() = 0;
			virtual void submit(const Renderable2D* renderable2d) = 0;
			virtual void drawString(const std::string& text, const maths::vec3& position, const Font& font, unsigned int color) = 0;
			virtual void end() = 0;
			virtual void flush() = 0;
		};
	}
}