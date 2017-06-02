#pragma once
#include <string>
#include <GL/glew.h>

#include "../maths/vec2.h"
#include "../maths/vec3.h"
#include "../maths/vec4.h"
#include "../maths/mat4.h"

namespace miniEngine
{
	namespace graphics
	{
		class Shader
		{
		private:
			GLuint m_programID;
			std::string m_verPath;
			std::string m_fragPath;
		public:
			Shader(const std::string& verPath, const std::string& fragPath);
			~Shader();

			void setUniform1i(const GLchar* name, int value);
			void setUniform1f(const GLchar* name, float value);
			void setUniform2f(const GLchar* name, const maths::vec2& vector);
			void setUniform3f(const GLchar* name, const maths::vec3& vector);
			void setUniform4f(const GLchar* name, const maths::vec4& vector);
			void setUniformMat4(const GLchar* name, const maths::mat4& matrix);

			void enable() const;
			void disable() const;

		private:
			GLuint load();
			GLint getUniformLocation(const GLchar* name);
		};
	}
}