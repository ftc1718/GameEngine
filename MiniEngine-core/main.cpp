//#include "src/graphics/window.h"
//#include <iostream>
//#include "src\maths\maths.h"
//#include "src\utility\fileUtils.h"
//
//int main()
//{
//	using namespace miniEngine;
//	using namespace graphics;
//	using namespace maths;
//	using namespace utils;
//
////	const GLubyte* s = glGetString(GL_EXTENSIONS);
//	Window window("Engine", 800, 600);
//	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
//
//	GLuint vao;
//	glGenVertexArrays(1, &vao);
//	glBindVertexArray(vao);
//
//	vec4 a(0.1f, 0.2f, 0.3f, 1.0f);
//	vec4 b(0.3f, 0.2f, 0.5f, 1.0f);
//
//	vec4 c = a * b;
//
//	mat4 position1 = mat4::translate(vec3(2.0f, 3.0f, 4.0f));
//	mat4 position2 = mat4::scale(vec3(5.0f, 2.0f, 3.0f));
//
//	position1 *= position2;
//	position1.elements[12] = 2.0f;
//
//	vec4 &c0 = position1.rows[3];
//	vec4 c1 = position1.getColumn(3);
//	std::cout << &position1.elements[12] << std::endl;
//	std::cout << &c1.x << std::endl;
//
//	while (!window.closed())
//	{
//		window.clear();
//
//#if 1
//		glBegin(GL_TRIANGLES);
//		glVertex2d(-0.5f, -0.5f);
//		glVertex2d(0.0f, 0.5f);
//		glVertex2d(0.5f, -0.5f);
//		glEnd();
//#else
//		glDrawArrays(GL_ARRAY_BUFFER, 0, 6);
//#endif
//		window.update();
//	}
//
//	return 0;
//}

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "src/maths/mat4.h"
#include "src/graphics/shaders.h"

int main()
{
	using namespace miniEngine;
	using namespace maths;
	using namespace graphics;
	glfwInit();
	
	GLFWwindow* window;
	window = glfwCreateWindow(960, 540, "Tutorial", NULL, NULL);
	glfwMakeContextCurrent(window);

	if (glewInit() == GLEW_OK)
		std::cout << "glew init ok!" << std::endl;
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);



	GLfloat bufferData[] = 
	{
		/*-0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,*/
		0,0,0,
		0,1,0,
		2,0,0
	};

	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(bufferData), bufferData, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0, -1.0f, 1.0f);

	Shader shader("src/shaders/vertexShader.shader", "src/shaders/fragmentShader.shader");
	shader.enable();

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);	
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}


//int main(void)
//{
//	// Initialise GLFW
//	if (!glfwInit())
//	{
//		fprintf(stderr, "Failed to initialize GLFW\n");
//		getchar();
//		return -1;
//	}
//
//
//	// Open a window and create its OpenGL context
//	GLFWwindow* window;
//	window = glfwCreateWindow(800, 600, "Tutorial 02 - Red triangle", NULL, NULL);
//	if (window == NULL) {
//		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
//		getchar();
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//
//	// Initialize GLEW
////	glewExperimental = true; // Needed for core profile
//	if (glewInit() != GLEW_OK) {
//		fprintf(stderr, "Failed to initialize GLEW\n");
//		getchar();
//		glfwTerminate();
//		return -1;
//	}
//
//	// Ensure we can capture the escape key being pressed below
//	// Dark blue background
//	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//
//
//	// Create and compile our GLSL program from the shaders
////	GLuint programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");
//
//
//	 GLfloat g_vertex_buffer_data[] = {
//		-0.5f, -0.5f,0.0f,
//		0.0f, 0.5f,0.0f,
//	0.5f, -0.5f,0.0f
//	};	
//	
//	GLuint vertexbuffer;
//	glGenBuffers(1, &vertexbuffer);
//	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
//
//
//	while (!glfwWindowShouldClose(window))
//	{
//		// Clear the screen
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		// Use our shader
////		glUseProgram(programID);
//
//		// 1rst attribute buffer : vertices
//		glEnableVertexAttribArray(0);
//		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
//		glVertexAttribPointer(
//			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
//			3,                  // size
//			GL_FLOAT,           // type
//			GL_FALSE,           // normalized?
//			0,                  // stride
//			(void*)0            // array buffer offset
//		);
//
//		// Draw the triangle !
//		glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle
//
//		glDisableVertexAttribArray(0);
//
//		// Swap buffers
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//
//	} // Check if the ESC key was pressed or the window was closed
//
//	// Cleanup VBO
//	//glDeleteBuffers(1, &vertexbuffer);
////	glDeleteVertexArrays(1, &VertexArrayID);
////	glDeleteProgram(programID);
//
//	// Close OpenGL window and terminate GLFW
//	glfwTerminate();
//
//	return 0;
//}
