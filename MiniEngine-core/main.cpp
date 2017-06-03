#include "src/graphics/window.h"
#include <iostream>
#include "src/maths/maths.h"
#include "src/graphics/shaders.h"

int main()
{
	using namespace miniEngine;
	using namespace graphics;
	using namespace maths;

	Window window("Engine", 960, 540);
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	GLfloat vertices[] =
	{
		/*-0.5, -0.5, 0,
		-0.5, 0.5, 0,
		0.5, 0.5, 0*/
		0, 0, 0,
		8, 0, 0,
		0, 3, 0,
		0, 3, 0,
		8, 3, 0,
		8, 0, 0
	};

	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader shader("src/shaders/vertexShader.shader", "src/shaders/fragmentShader.shader");
	shader.enable();

	shader.setUniformMat4("projectionMatrix", ortho);
	shader.setUniformMat4("modelMatrix", mat4::translate(vec3(4, 3, 0)));

	shader.setUniform4f("colour", vec4(1.0f, 0.0f, 0.0f, 1.0f));
	//使光源位于中心 （4,1.5）是相对坐标 （8，4.5）是绝对坐标
	//坐标系在vectexShader中调整
	shader.setUniform2f("lightPosition", vec2(4, 1.5));

	while (!window.closed())
	{
		window.clear();
		glDrawArrays(GL_TRIANGLES, 0, 6);

		window.update();
	}

	return 0;
}
//
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include <iostream>
//
//#include "src/maths/mat4.h"
//#include "src/graphics/shaders.h"
//
//int main()
//{
//	using namespace miniEngine;
//	using namespace maths;
//	using namespace graphics;
//	glfwInit();
//	
//	GLFWwindow* window;
//	window = glfwCreateWindow(960, 540, "Tutorial", NULL, NULL);
//	glfwMakeContextCurrent(window);
//
//	if (glewInit() == GLEW_OK)
//		std::cout << "glew init ok!" << std::endl;
////	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
//
//
//
//	GLfloat bufferData[] = 
//	{
//		/*-0.5f, -0.5f, 0.0f,
//		-0.5f, 0.5f, 0.0f,
//		0.5f, 0.5f, 0.0f,
//		0.5f, 0.5f, 0.0f,
//		0.5f, -0.5f, 0.0f,
//		-0.5f, -0.5f, 0.0f,*/
//		/*4,3,0,
//		12,3,0,
//		4,6,0,
//		4,6,0,
//		12,6,0,
//		12,3,0*/
//		0, 0, 0,
//		8, 0, 0,
//		0, 3, 0,
//		0, 3, 0,
//		8, 3, 0,
//		8, 0, 0
//	};
//
//	GLuint vertexBuffer;
//	glGenBuffers(1, &vertexBuffer);
//	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(bufferData), bufferData, GL_STATIC_DRAW);
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//	glEnableVertexAttribArray(0);
//
//	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0, -1.0f, 1.0f);
//
//	Shader shader("src/shaders/vertexShader.shader", "src/shaders/fragmentShader.shader");
//	shader.enable();
//	shader.setUniformMat4("projectionMatrix", ortho);
////	shader.setUniformMat4("modelMatrix", mat4::rotate(45.0f, vec3(0, 0, 1)));
//	shader.setUniformMat4("modelMatrix", mat4::translate(vec3(4, 3, 0)));
//
//	shader.setUniform2f("lightPosition", vec2(8, 4.5));
//
//	shader.setUniform4f("colour", vec4(0.2f, 0.3f, 0.8f, 1.0f));
//
//	while (!glfwWindowShouldClose(window))
//	{
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		glDrawArrays(GL_TRIANGLES, 0, 6);
//
//		glfwSwapBuffers(window);	
//		glfwPollEvents();
//	}
//
//	glfwTerminate();
//	return 0;
//}

