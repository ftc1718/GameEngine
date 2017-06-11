#if 1

#include <iostream>
#include <vector>
#include "src/utility/timer.h"

#include "src/graphics/window.h"
#include "src/maths/maths.h"
#include "src/graphics/shaders.h"

#include "src/graphics/buffers/buffer.h"
#include "src/graphics/buffers/indexBuffer.h"
#include "src/graphics/buffers/vertexArray.h"

#include "src/graphics/renderer2d.h"
#include "src/graphics/simple2dRenderer.h"
#include "src/graphics/batchRenderer2d.h"

#include "src/graphics/staticSprite.h"
#include "src/graphics/Sprite.h"

#include "src/graphics/layers/tileLayer.h"

#include <time.h>


/*Engine Test*/
int main()
{
	using namespace MiniEngine;
	using namespace graphics;
	using namespace maths;

	Window window("Engine", 960, 540);
	//	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

//	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader* s = new Shader("src/shaders/vertexShader.shader", "src/shaders/fragmentShader.shader");
	Shader* s2 = new Shader("src/shaders/vertexShader.shader", "src/shaders/fragmentShader.shader");
	Shader& shader = *s;
	Shader& shader2 = *s2;
	shader.enable();
	shader2.enable();
	shader.setUniform2f("lightPosition", vec2(4, 1.5));
	shader2.setUniform2f("lightPosition", vec2(4, 1.5));

	TileLayer layer(&shader);
	for (float y = -9.0f; y < 9.0f; y += 0.1)
	{
		for (float x = -16.0f; x < 16.0f; x += 0.1)
		{
			layer.add(new Sprite(x, y, 0.09f, 0.09f, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
		}
	}

	TileLayer layer2(&shader2);
	layer2.add(new Sprite(-2, -2, 4, 4, vec4(0.8f, 0.2f, 0.8f, 1.0f)));

	Timer timer;
	double time = 0;
	unsigned int frames = 0;
	while (!window.closed())
	{
		window.clear();
		double x, y;
		window.getMousePosition(x, y);
		shader.enable();
		shader.setUniform2f("lightPosition", vec2((float)(x * 32.0f / 960.0f - 16.0f), (float)(9.0f - y * 18.0f / 540.0f)));
//		shader.setUniform2f("lightPosition", vec2(-8, -3));
		shader2.enable();
		shader2.setUniform2f("lightPosition", vec2((float)(x * 32.0f / 960.0f - 16.0f), (float)(9.0f - y * 18.0f / 540.0f)));

		layer.render();
		layer2.render();

		window.update();
		frames++;
		if (timer.elasped() - time > 1.0f)
		{
			time += 1.0f;
			printf("%d fps\n", frames);
			frames = 0;
		}
	}
	return 0;
}


#else
/* OpenGL Tutorial*/
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "src/maths/mat4.h"
#include "src/graphics/shaders.h"
#include "src/maths/mat4.h"

int main()
{
	using namespace MiniEngine;
	using namespace maths;
	using namespace graphics;

	glfwInit();

	GLFWwindow* window;
	window = glfwCreateWindow(1024, 768, "Tutorial", NULL, NULL);
	glfwMakeContextCurrent(window);

	if (glewInit() == GLEW_OK)
		std::cout << "glew init ok!" << std::endl;
	//	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);



	GLfloat bufferData[] =
	{
		-1, -1, 0,
		0, -1, 1,
		1, -1, 0,
		0, 1, 0
		/*-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,*/
		/*-0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,*/
		/*-0.5f,-0.5f,-0.5f,
		-0.5f,-0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,
		0.5f, 0.5f,-0.5f,
		-0.5f,-0.5f,-0.5f,
		-0.5f, 0.5f,-0.5f,
		0.5f,-0.5f, 0.5f,
		-0.5f,-0.5f,-0.5f,
		0.5f,-0.5f,-0.5f,
		0.5f, 0.5f,-0.5f,
		0.5f,-0.5f,-0.5f,
		-0.5f,-0.5f,-0.5f,
		-0.5f,-0.5f,-0.5f,
		-0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f,-0.5f,
		0.5f,-0.5f, 0.5f,
		-0.5f,-0.5f, 0.5f,
		-0.5f,-0.5f,-0.5f,
		-0.5f, 0.5f, 0.5f,
		-0.5f,-0.5f, 0.5f,
		0.5f,-0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		0.5f,-0.5f,-0.5f,
		0.5f, 0.5f,-0.5f,
		0.5f,-0.5f,-0.5f,
		0.5f, 0.5f, 0.5f,
		0.5f,-0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		0.5f, 0.5f,-0.5f,
		-0.5f, 0.5f,-0.5f,
		0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f,-0.5f,
		-0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,
		0.5f,-0.5f, 0.5f*/
		//-0.5f, -0.5f, -0.5f,
		//0.5f, -0.5f, -0.5f,
		//-0.5f, 0.5f, -0.5f, //背面第一个三角形
		//0.5f, 0.5f, -0.5f,
		//-0.5f, 0.5f, -0.5f,
		//0.5f, -0.5f, -0.5f,//
		//-0.5f, -0.5f, 0.5f,
		//0.5f, -0.5f, 0.5f,
		//-0.5f, 0.5f, 0.5f,//qianmian1
		//0.5f, 0.5f, 0.5f,
		//-0.5f, 0.5f, 0.5f,
		//0.5f, -0.5f, 0.5f,//2
		//-0.5f, 0.5f, 0.5f,
		//0.5f, 0.5f, 0.5f,
		//-0.5f, 0.5f, -0.5f,//shangmian1
		//0.5f, 0.5f, -0.5f,
		//0.5f, 0.5f, 0.5f,
		//-0.5f, 0.5f, -0.5f,//2
		//-0.5f, -0.5f, 0.5f,
		//0.5f, -0.5f, 0.5f,
		//-0.5f, -0.5f, -0.5f,//xiamian1
		//0.5f, -0.5f, -0.5f,
		//0.5f, -0.5f, 0.5f,
		//-0.5f, -0.5f, -0.5f,//2
		//-0.5f, -0.5f, 0.5f,
		//-0.5f, -0.5f, -0.5f,
		//-0.5f, 0.5f, 0.5f, //zuomian 1
		//-0.5f, 0.5f, -0.5f,
		//-0.5f, 0.5f, 0.5f,
		//-0.5f, -0.5f, -0.5f,//2
		//0.5f, -0.5f, 0.5f,
		//0.5f, -0.5f, -0.5f,
		//0.5f, 0.5f, 0.5f, //youmian 1
		//0.5f, 0.5f, -0.5f,
		//0.5f, 0.5f, 0.5f,
		//0.5f, -0.5f, -0.5f,//2
	};

	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(bufferData), bufferData, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	unsigned int indices[] =
	{
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLuint indexBuffer;
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	GLfloat g_color_buffer_data[] = {
		0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		0.822f,  0.569f,  0.201f,
		0.435f,  0.602f,  0.223f,
		0.310f,  0.747f,  0.185f,
		0.597f,  0.770f,  0.761f,
		0.559f,  0.436f,  0.730f,
		0.359f,  0.583f,  0.152f,
		0.483f,  0.596f,  0.789f,
		0.559f,  0.861f,  0.639f,
		0.195f,  0.548f,  0.859f,
		0.014f,  0.184f,  0.576f,
		0.771f,  0.328f,  0.970f,
		0.406f,  0.615f,  0.116f,
		0.676f,  0.977f,  0.133f,
		0.971f,  0.572f,  0.833f,
		0.140f,  0.616f,  0.489f,
		0.997f,  0.513f,  0.064f,
		0.945f,  0.719f,  0.592f,
		0.543f,  0.021f,  0.978f,
		0.279f,  0.317f,  0.505f,
		0.167f,  0.620f,  0.077f,
		0.347f,  0.857f,  0.137f,
		0.055f,  0.953f,  0.042f,
		0.714f,  0.505f,  0.345f,
		0.783f,  0.290f,  0.734f,
		0.722f,  0.645f,  0.174f,
		0.302f,  0.455f,  0.848f,
		0.225f,  0.587f,  0.040f,
		0.517f,  0.713f,  0.338f,
		0.053f,  0.959f,  0.120f,
		0.393f,  0.621f,  0.362f,
		0.673f,  0.211f,  0.457f,
		0.820f,  0.883f,  0.371f,
		0.982f,  0.099f,  0.879f
	};

	GLuint colorBuffer;
	glGenBuffers(1, &colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	Shader shader("src/shaders/vertexShader.tutorial", "src/shaders/fragmentShader.tutorial");
	shader.enable();

	/*mat4 pers = mat4::perspective(45.0f, (float)1024 / (float)768, 0.1f, 100.0f);
	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);*/

	shader.setUniformMat4("projectionMatrix", mat4::rotate(45, vec3(1, 0, 0)));

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//		glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
		glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

#endif
