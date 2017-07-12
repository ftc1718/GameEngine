#include "window.h"
#include <iostream>

namespace indie
{
	namespace graphics
	{

		void windowResize(GLFWwindow* window, int width, int height);
		void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);

		//static value must be declare out the .h
		/*bool Window::m_keys[MAX_KEYS];
		bool Window::m_mouseButtons[MAX_BUTTONS];
		double Window::m_x;
		double Window::m_y;*/
		Window::Window(const char* title, int width, int height)
			: m_pTitle(title), m_width(width), m_height(height)
		{
			if (!init())
			{
				glfwTerminate();
			}

#ifdef INDIE_EMSCRIPTEN
			FontManager::add((new Font("SourceSansPro-Light", "res/SourceSansPro-Light.ttf", 32)));
			FreeImage_Initialise();
#else
			//default font
			FontManager::add((new Font("SourceSansPro-Light", "SourceSansPro-Light.ttf", 32)));
#endif

#ifndef INDIE_EMSCRIPTEN
			audio::SoundManager::init();
#endif

			for (int i = 0; i < MAX_KEYS; ++i)
			{
				m_keys[i] = false;
				m_keyState[i] = false;
				m_keyTyped[i] = false;
			}

			for (int i = 0; i < MAX_BUTTONS; ++i)
			{
				m_mouseButtons[i] = false;
				m_mouseState[i] = false;
				m_mouseClicked[i] = false;
			}
		}

		Window::~Window()
		{
			FontManager::clean();

#ifndef INDIE_EMSCRIPTEN
			audio::SoundManager::clean();
#endif

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

			glfwSetFramebufferSizeCallback(m_pWindow, windowResize);
			glfwSetKeyCallback(m_pWindow, keyCallback);
			glfwSetMouseButtonCallback(m_pWindow, mouseButtonCallback);
			glfwSetCursorPosCallback(m_pWindow, cursorPositionCallback);

			glfwSwapInterval(0);//关闭垂直同步

#ifndef INDIE_EMSCRIPTEN
			if (glewInit() != GLEW_OK)
			{
				std::cout << "Could not initialize GLEW!" << std::endl;
				return false;
			}
#endif

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
			for (int i = 0; i < MAX_KEYS; i++)
			{
				m_keyTyped[i] = m_keys[i] && !m_keyState[i];
			}
			
			for (int i = 0; i < MAX_BUTTONS; i++)
			{
				m_mouseClicked[i] = m_mouseButtons[i] && !m_mouseState[i];
			}

			memcpy(m_keyState, m_keys, MAX_KEYS);
			memcpy(m_mouseState, m_mouseButtons, MAX_BUTTONS);

			GLenum error = glGetError();
			if (error != GL_NO_ERROR)
			{
				std::cout << "OpenGL Error: " << error << std::endl;
			}
			glfwPollEvents();
			glfwSwapBuffers(m_pWindow);

#ifndef INDIE_EMSCRIPTEN
			audio::SoundManager::update();
#endif

		}

		bool Window::isKeyPressed(unsigned int keyCode) const
		{
			if (keyCode >= MAX_KEYS)
			{
				return false;
			}

			return m_keys[keyCode];
		}

		bool Window::isKeyTyped(unsigned int keyCode) const
		{
			if (keyCode >= MAX_KEYS)
			{
				return false;
			}

			return m_keyTyped[keyCode];
		}

		bool Window::isMouseButtonPressed(unsigned int mouseButton) const
		{
			if (mouseButton >= MAX_BUTTONS)
			{
				return false;
			}

			return m_mouseButtons[mouseButton];
		}

		bool Window::isMouseButtonClicked(unsigned int mouseButton) const
		{
			if (mouseButton >= MAX_BUTTONS)
			{
				return false;
			}

			return m_mouseClicked[mouseButton];
		}

		void Window::getMousePosition(double& x, double& y) const
		{
			x = m_x;
			y = m_y;
		}

		void windowResize(GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_width = width;
			win->m_height = height;
		}

		void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_keys[key] = action != GLFW_RELEASE;
		}

		void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_mouseButtons[button] = action != GLFW_RELEASE;
		}

		void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_x = xpos;
			win->m_y = ypos;
		}
	}
}