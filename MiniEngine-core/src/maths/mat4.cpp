#include "mat4.h"
#include "maths.h"


namespace MiniEngine
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
			//row save
			/*float tmpData[16];
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

			memcpy(elements, tmpData, 4 * 4 * sizeof(float));*/

			float tmpData[16];
			for (int y = 0; y < 4; y++)
			{
				for (int x = 0; x < 4; x++)
				{
					float sum = 0.0f;
					for (int e = 0; e < 4; e++)
					{
						sum += elements[x + e * 4] * other.elements[e + y * 4];
					}
					tmpData[x + y * 4] = sum;
				}
			}
			memcpy(elements, tmpData, 4 * 4 * sizeof(float));

			return *this;
		}

		mat4 operator*(mat4 left, const mat4& right)
		{
			return left.multiply(right);
		}

		mat4& mat4::operator*=(const mat4& other)
		{
			return multiply(other);
		}

		vec3 mat4::multiply(const vec3& other) const
		{
			return vec3(
				columns[0].x * other.x + columns[1].x * other.y + columns[2].x * other.z + columns[3].x,
				columns[0].y * other.x + columns[1].y * other.y + columns[2].y * other.z + columns[3].y,
				columns[0].z * other.x + columns[1].z * other.y + columns[2].z * other.z + columns[3].z
			);
		}

		vec3 operator*(const mat4& left, const vec3& right)
		{
			return left.multiply(right);
		}

		//column save
		vec4 mat4::multiply(const vec4& other) const
		{
			return vec4(
				columns[0].x * other.x + columns[1].x * other.y + columns[2].x * other.z + columns[3].x * other.w,
				columns[0].y * other.x + columns[1].y * other.y + columns[2].y * other.z + columns[3].y * other.w,
				columns[0].z * other.x + columns[1].z * other.y + columns[2].z * other.z + columns[3].z * other.w,
				columns[0].w * other.x + columns[1].w * other.y + columns[2].w * other.z + columns[3].w * other.w
			);
		}

		vec4 operator*(const mat4& left, const vec4& right)
		{
			return left.multiply(right);
		}

		//row save
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

			//row save
			/*mat4 result(1.0f);

			result.elements[0 + 0 * 4] = 2.0f / (right - left);
			result.elements[1 + 1 * 4] = 2.0f / (top - bottom);
			result.elements[2 + 2 * 4] = -2.0f / (far - near);

			result.elements[3 + 0 * 4] = -(right + left) / (right - left);
			result.elements[3 + 1 * 4] = -(top + bottom) / (top - bottom);
			result.elements[3 + 2 * 4] = -(far + near) / (far - near);*/

			return result;
		}

		//aspectRatio表示屏幕宽高比
		mat4 mat4::perspective(float fov, float aspectRatio, float near, float far)
		{
			mat4 result(1.0f);

			float q = 1.0f / tan(toRadians(0.5f * fov));
			float a = q / aspectRatio;

			float b = (near + far) / (near - far);
			float c = (2.0f * near * far) / (near - far);

			result.elements[0 + 0 * 4] = a;
			result.elements[1 + 1 * 4] = q;
			result.elements[2 + 2 * 4] = b;
			result.elements[3 + 2 * 4] = -1.0f;
			result.elements[2 + 3 * 4] = c;

//			result.elements[3 + 3 * 4] = 0.0f;


			//row save
			/*float q = 1.0f / tan(toRadians(0.5f * fov));
			float a = q / aspectRatio;

			result.elements[0 + 0 * 4] = a;
			result.elements[1 + 1 * 4] = q;
			result.elements[2 + 2 * 4] = (far + near) / (near - far);
			result.elements[3 + 3 * 4] = 0.0f;

			result.elements[3 + 2 * 4] = 2.0f * far * near / (near - far);
			result.elements[2 + 3 * 4] = -1.0f;
*/
		
			return result;
		}

		mat4 mat4::translate(const vec3& translation)
		{
			mat4 result(1.0f);

			//translation matrix
			//平移点以列向量表示 a = 
			//平移距离为矩阵最后一列
			//如此链接中的平移矩阵http://www.opengl-tutorial.org/cn/beginners-tutorials/tutorial-3-matrices/
			/*result.elements[3 + 0 * 4] = translation.x;
			result.elements[3 + 1 * 4] = translation.y;
			result.elements[3 + 2 * 4] = translation.z;
*/

			//平移点以行向量表示 a = (10, 10, 10 ,1)
			//平移距离为矩阵最后一行
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