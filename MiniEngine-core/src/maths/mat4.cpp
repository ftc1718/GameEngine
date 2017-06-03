#include "mat4.h"
#include "maths.h"


namespace miniEngine
{
	namespace maths
	{
		mat4::mat4()
		{
			memset(elements, 0, 4 * 4 * sizeof(float));
		}

		mat4::mat4(float diagonal)
		{
			memset(elements, 0, 4 * 4 * sizeof(float));
			elements[0 + 0 * 4] = diagonal;
			elements[1 + 1 * 4] = diagonal;
			elements[2 + 2 * 4] = diagonal;
			elements[3 + 3 * 4] = diagonal;
		}

		mat4 mat4::identity()
		{
			return mat4(1.0f);
		}

		mat4& mat4::multiply(const mat4& other)
		{
			float tmpData[16];
			for (int row = 0; row < 4; ++row)
			{
				for (int col = 0; col < 4; ++col)
				{
					float sum = 0.0f;
					for (int i = 0; i < 4; ++i)
					{
						sum += elements[i + row * 4] * other.elements[col + i * 4];
					}
					tmpData[col + row * 4] = sum;
				}
			}

			memcpy(elements, tmpData, 4 * 4 * sizeof(float));
			return *this;
		}

		mat4 operator*(mat4 left, mat4& right)
		{
			return left.multiply(right);
		}

		mat4& mat4::operator*=(const mat4& other)
		{
			return multiply(other);
		}

		vec4 mat4::getColumn(int index) const
		{
			return vec4(elements[index + 0 * 4], elements[index + 1 * 4], elements[index + 2 * 4], elements[index + 3 * 4]);
		}

		//长方体视景体，由该视景体观察xy平面
		//参考http://blog.sina.com.cn/s/blog_6471e1bb0102vtv1.html
		mat4 mat4::orthographic(float left, float right, float bottom, float top, float near, float far)
		{

			mat4 result(1.0f);

			result.elements[0 + 0 * 4] = 2.0f / (right - left);

			result.elements[1 + 1 * 4] = 2.0f / (top - bottom);

			result.elements[2 + 2 * 4] = 2.0f / (near - far);

			result.elements[0 + 3 * 4] = (left + right) / (left - right);
			result.elements[1 + 3 * 4] = (bottom + top) / (bottom - top);
			result.elements[2 + 3 * 4] = (far + near) / (far - near);
			/*mat4 result(1.0f);

			result.elements[0 + 0 * 4] = 2.0f / (right - left);
			result.elements[1 + 1 * 4] = 2.0f / (top - bottom);
			result.elements[2 + 2 * 4] = -2.0f / (far - near);

			result.elements[3 + 0 * 4] = -(right + left) / (right - left);
			result.elements[3 + 1 * 4] = -(top + bottom) / (top - bottom);
			result.elements[3 + 2 * 4] = -(far + near) / (far - near);*/

			return result;
		}

		mat4 mat4::perspective(float fov, float aspectRatio, float near, float far)
		{
			mat4 result(1.0f);

			float q = 1.0f / tan(toRadians(0.5f * fov));
			float a = q / aspectRatio;

			result.elements[0 + 0 * 4] = a;
			result.elements[1 + 1 * 4] = q;
			result.elements[2 + 2 * 4] = (far + near) / (near - far);
			result.elements[3 + 3 * 4] = 0.0f;

			result.elements[3 + 2 * 4] = 2.0f * far * near / (near - far);
			result.elements[2 + 3 * 4] = -1.0f;

			return result;
		}

		mat4 mat4::translate(const vec3& translation)
		{
			mat4 result(1.0f);

			/*result.elements[3 + 0 * 4] = translation.x;
			result.elements[3 + 1 * 4] = translation.y;
			result.elements[3 + 2 * 4] = translation.z;
*/
			result.elements[0 + 3 * 4] = translation.x;
			result.elements[1 + 3 * 4] = translation.y;
			result.elements[2 + 3 * 4] = translation.z;
			return result;

		}

		mat4 mat4::rotate(float angle, const vec3& Rotation)
		{
			mat4 result(1.0f);

			float r = toRadians(angle);
			float s = sin(r);
			float c = cos(r);
			float omc = 1.0f - c;

			float x = Rotation.x;
			float y = Rotation.y;
			float z = Rotation.z;

			/*result.elements[0 + 0 * 4] = x * x * omc + c;
			result.elements[0 + 1 * 4] = x * y * omc + z * s;
			result.elements[0 + 2 * 4] = x * z * omc - y * s;

			result.elements[1 + 0 * 4] = x * y * omc - z * s;
			result.elements[1 + 1 * 4] = y * y * omc + c;
			result.elements[1 + 2 * 4] = y * z * omc + x * s;

			result.elements[2 + 0 * 4] = x * z * omc + y * s;
			result.elements[2 + 1 * 4] = y * z * omc - x * s;
			result.elements[2 + 2 * 4] = z * z * omc + c;*/

			result.elements[0 + 0 * 4] = x * omc + c;
			result.elements[1 + 0 * 4] = y * x * omc + z * s;
			result.elements[2 + 0 * 4] = x * z * omc - y * s;

			result.elements[0 + 1 * 4] = x * y * omc - z * s;
			result.elements[1 + 1 * 4] = y * omc + c;
			result.elements[2 + 1 * 4] = y * z * omc + x * s;

			result.elements[0 + 2 * 4] = x * z * omc + y * s;
			result.elements[1 + 2 * 4] = y * z * omc - x * s;
			result.elements[2 + 2 * 4] = z * omc + c;

			return result;
		}

		mat4 mat4::scale(const vec3& scale)
		{
			mat4 result(1.0f);

			result.elements[0 + 0 * 4] = scale.x;
			result.elements[1 + 1 * 4] = scale.y;
			result.elements[2 + 2 * 4] = scale.z;

			return result;
		}
	}
}