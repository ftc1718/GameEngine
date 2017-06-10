#include "window.h"
#include <iostream>

namespace MiniEngine
{
	namespace graphics
	{
		//static value must be declare out the .h
		/*bool Window::m_keys[MAX_KEYS];
		bool Window::m_mouseButtons[MAX_BUTTONS];
		double Window::m_x;
		double Window::m_y;*/
		
		void windowResize(GLFWwindow* window, int width, int height);
		
		Window::Window(const char* title, int width, int height)
			: m_pTitle(title), m_width(width), m_height(height)
		{
			if (!init())
			{
				glfwTerminate();
			}

			for (int i = 0; i < MAX_KEYS; ++i)
			{
				m_keys[i] = false;
			}

			for (int i = 0; i < MAX_BUTTONS; ++i)
			{
				m_mouseButtons[i] = false;
			}
		}

		Window::~Window()
		{
			glfwTerminate();
		}

		bool Window::init()
		{
			if (!glfwInit())
			{
				std::cout << "Failed to initialize GLFW!" << std::endl;
				return false;
			}

			m_pWindow = glfwCreateWindow(m_width, m_height, m_pTitle, NULL, NULL);
			if (!m_pWindow)
			{
				std::cout << "Fail to create GLFW window" << std::endl;
				return false;
			}
			glfwMakeContextCurrent(m_pWindow);
			glfwSetWindowUserPointer(m_pWindow, this);

			glfwSetWindowSizeCallback(m_pWindow, windowResize);
			glfwSetKeyCallback(m_pWindow, keyCallback);
			glfwSetMouseButtonCallback(m_pWindow, mouseButtonCallback);
			glfwSetCursorPosCallback(m_pWindow, cursorPositionCallback);

			glfwSwapInterval(0);//关闭垂直同步


			if (glewInit() != GLEW_OK)
			{
				std::cout << "Could not initialize GLEW!" << std::endl;
				return false;
			}

			std::cout << "OpenGL" << glGetString(GL_VERSION) << std::endl;

			return true;

		}

		bool Window::closed() const
		{
			return glfwWindowShouldClose(m_pWindow) == 1;
		}

		void Window::clear() const
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Window::update()
		{
			GLenum error = glGetError();
			if (error != GL_NO_ERROR)
			{
				std::cout << "OpenGL Error: " << error << std::endl;
			}
			glfwPollEvents();
			glfwSwapBuffers(m_pWindow);
		}

		void windowResize(GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
		}

		bool Window::isKeyPressed(unsigned int keyCode) const
		{
			if (keyCode >= MAX_KEYS)
			{
				return false;
			}

			return m_keys[keyCode];
		}

		bool Window::isMouseButtonPressed(unsigned int mouseButton) const
		{
			if (mouseButton >= MAX_BUTTONS)
			{
				return false;
			}

			return m_mouseButtons[mouseButton];
		}

		void Window::getMousePosition(double& x, double& y) const
		{
			x = m_x;
			y = m_y;
		}

		void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			Window *win = (Window*)glfwGetWindowUserPointer(window);
			win->m_keys[key] = action != GLFW_RELEASE;
		}

		void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
		{
			Window *win = (Window*)glfwGetWindowUserPointer(window);
			win->m_mouseButtons[button] = action != GLFW_RELEASE;
		}

		void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
		{
			Window *win = (Window*)glfwGetWindowUserPointer(window);
			win->m_x = xpos;
			win->m_y = ypos;
		}
	}
}