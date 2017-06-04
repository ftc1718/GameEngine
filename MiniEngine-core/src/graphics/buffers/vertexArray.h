#pragma once
#include <vector>
#include <GL/glew.h>

#include "buffer.h"

//每一个需要渲染的物体包含的buffer（顶点buffer，颜色buffer）

namespace MiniEngine
{
	namespace graphics
	{
		class VertexArray
		{
		private:
			GLuint m_arrayID;
		public:
			VertexArray();
			
			void addBuffer(Buffer* buffer, GLuint index);
			void bind() const;
			void unbind() const;
		};
	}
}