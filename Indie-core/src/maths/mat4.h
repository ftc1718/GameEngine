#pragma once

#include "vec3.h"
#include "vec4.h"

namespace Indie
{
	namespace maths
	{
		struct mat4
		{
			union
			{
				float elements[4 * 4];
				//vec4 rows[4];
				vec4 columns[4];//°´ÁÐ´æ´¢
			};

			mat4();
			mat4(float diagonal);

			static mat4 identity();

			mat4& multiply(const mat4& other);
			friend mat4 operator*(mat4 left, const mat4& right);
			mat4& operator*=(const mat4& other);

			vec3 multiply(const vec3& other) const;
			friend vec3 operator*(const mat4& left, const vec3& right);

			vec4 multiply(const vec4& other) const;
			friend vec4 operator*(const mat4& left, const vec4& right);

			vec4 getColumn(int index) const;

			mat4& invert();

			static mat4 orthographic(float left, float right, float bottom, float top, float near, float far);
			static mat4 perspective(float fov, float aspectRatio, float near, float far);

			static mat4 translate(const vec3& translation);
			static mat4 rotate(float angle, const vec3& Rotation);
			static mat4 scale(const vec3& scale);
		};
	}
}