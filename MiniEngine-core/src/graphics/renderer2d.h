#pragma once

#include "renderable2d.h"

namespace MiniEngine
{
	namespace graphics
	{
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
			virtual void begin() { }
			virtual void submit(const Renderable2D* renderable2d) = 0;
			virtual void end() { }
			virtual void flush() = 0;
		};
	}
}