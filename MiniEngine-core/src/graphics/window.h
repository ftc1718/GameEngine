#pragma once 

#include <GL\glew.h>
#include <GLFW\glfw3.h>

namespace miniEngine
{
	namespace graphics
	{

#define MAX_KEYS		1024
#define MAX_BUTTONS		32	
		class Window
		{
		private:
			int m_width;
			int m_height;
			const char* m_title;
			GLFWwindow* m_window;

			//these can be static
			bool m_keys[MAX_KEYS];
			bool m_mouseButtons[MAX_BUTTONS];
			double m_x, m_y;

		public:
			Window(const char* title, int width, int height);
			~Window();
			bool closed() const;
			void update();
			void clear() const;

			inline int getWidth() const { return m_width; }
			inline int getHeight() const { return m_height; }

			//these can be static, can be called Window::isKeyPressed without an instances
			bool isKeyPressed(unsigned int keyCode) const;
			bool isMouseButtonPressed(unsigned int mouseButton) const;
			void getMousePosition(double& x, double& y) const;
		private:
			bool init();
			friend static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
			friend static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
			friend static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
		};
	}
}
