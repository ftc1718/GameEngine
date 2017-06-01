#include "src/graphics/window.h"
#include <iostream>
#include "src\maths\maths.h"
#include "src\utility\fileUtils.h"

int main()
{
	using namespace miniEngine;
	using namespace graphics;
	using namespace maths;
	using namespace utils;

	std::string file = readFile("main.cpp");
	std::cout << file << std::endl;
	system("PAUSE");
	return 0;

	Window window("Sparky", 800, 600);
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	vec4 a(0.1f, 0.2f, 0.3f, 1.0f);
	vec4 b(0.3f, 0.2f, 0.5f, 1.0f);

	vec4 c = a * b;

	mat4 position1 = mat4::translate(vec3(2.0f, 3.0f, 4.0f));
	mat4 position2 = mat4::scale(vec3(5.0f, 2.0f, 3.0f));

	position1 *= position2;
	position1.elements[12] = 2.0f;

	vec4 &c0 = position1.rows[3];
	vec4 c1 = position1.getColumn(3);
	std::cout << &position1.elements[12] << std::endl;
	std::cout << &c1.x << std::endl;

	while (!window.closed())
	{
		window.clear();

#if 1
		glBegin(GL_TRIANGLES);
		glVertex2d(-0.5f, -0.5f);
		glVertex2d(0.0f, 0.5f);
		glVertex2d(0.5f, -0.5f);
		glEnd();
#else
		glDrawArrays(GL_ARRAY_BUFFER, 0, 6);
#endif
		window.update();
	}

	return 0;
}