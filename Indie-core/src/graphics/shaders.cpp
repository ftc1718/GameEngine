#include <vector>
#include <iostream>

#include "shaders.h"
#include "../utility/fileUtils.h"

namespace indie
{
	namespace graphics
	{
		Shader::Shader(const std::string& verPath, const std::string& fragPath)
			: m_verPath(verPath), m_fragPath(fragPath)
		{
			m_programID = load();
		}

		Shader::~Shader()
		{
			glDeleteProgram(m_programID);
		}

		void Shader::setUniform1i(const GLchar* name, int value)
		{
			glUniform1i(getUniformLocation(name), value);
		}

		void Shader::setUniform1iv(const GLchar* name, int* value, int count)
		{
			glUniform1iv(getUniformLocation(name), count, value);
		}

		void Shader::setUniform1f(const GLchar* name, float value)
		{
			glUniform1f(getUniformLocation(name), value);
		}

		void Shader::setUniform1fv(const GLchar* name, float* value, int count)
		{
			glUniform1fv(getUniformLocation(name), count, value);
		}

		void Shader::setUniform2f(const GLchar* name, const maths::vec2& vector)
		{
			glUniform2f(getUniformLocation(name), vector.x, vector.y);
		}

		void Shader::setUniform3f(const GLchar* name, const maths::vec3& vector)
		{
			glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
		}

		void Shader::setUniform4f(const GLchar* name, const maths::vec4& vector)
		{
			glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
		}
		void Shader::setUniformMat4(const GLchar* name, const maths::mat4& matrix)
		{
			glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements);
		}

		void Shader::enable() const
		{
			glUseProgram(m_programID);
		}

		void Shader::disable() const
		{
			glUseProgram(0);
		}

		GLuint Shader::load()
		{
			GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
			GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

			std::string vertexSourceString = utils::readFile(m_verPath);
			std::string fragmentSourceString = utils::readFile(m_fragPath);

			const GLchar* vertexSource = vertexSourceString.c_str();
			const GLchar* fragmentSource = fragmentSourceString.c_str();

			glShaderSource(vertexShaderID, 1, &vertexSource, NULL);
			glCompileShader(vertexShaderID);

			GLint result = GL_FALSE;

			glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE)
			{
				GLint infoLogLength;
				glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
				std::vector<char> vertexShaderErrorMessage(infoLogLength + 1);
				glGetShaderInfoLog(vertexShaderID, infoLogLength, NULL, &vertexShaderErrorMessage[0]);
				std::cout << "Failed to compile vertex shader!" << std::endl << &vertexShaderErrorMessage[0] << std::endl;
				return 0;
			}


			glShaderSource(fragmentShaderID, 1, &fragmentSource, NULL);
			glCompileShader(fragmentShaderID);

			glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE)
			{
				GLint infoLogLength;
				glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
				std::vector<char> fragmentShaderErrorMessage(infoLogLength + 1);
				glGetShaderInfoLog(fragmentShaderID, infoLogLength, NULL, &fragmentShaderErrorMessage[0]);
				std::cout << "Failed to compile fragment shader!" << std::endl << &fragmentShaderErrorMessage[0] << std::endl;
				return 0;
			}

			GLuint programID = glCreateProgram();
			glAttachShader(programID, vertexShaderID);
			glAttachShader(programID, fragmentShaderID);

			glLinkProgram(programID);
			glValidateProgram(programID);

			glDetachShader(programID, vertexShaderID);
			glDetachShader(programID, fragmentShaderID);

			glDeleteShader(vertexShaderID);
			glDeleteShader(fragmentShaderID);

			return programID;
		}

		GLint Shader::getUniformLocation(const GLchar* name)
		{
			return glGetUniformLocation(m_programID, name);
		}

	}
}