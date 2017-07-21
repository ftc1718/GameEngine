#pragma once 

#ifdef INDIE_EMSCRIPTEN
	#define GLFW_INCLUDE_ES3
	#include <FreeImage.h>
#else
	#include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>
#include "../maths/vec2.h"
#include "fontManager.h"
#include "textureManager.h"
#include "../audio/soundManager.h"

namespace indie
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
			const char* m_pTitle;
			GLFWwindow* m_pWindow;

			//these can be static
			bool m_keys[MAX_KEYS];
			bool m_keyState[MAX_KEYS];
			bool m_keyTyped[MAX_KEYS];
			bool m_mouseButtons[MAX_BUTTONS];
			bool m_mouseState[MAX_BUTTONS];
			bool m_mouseClicked[MAX_BUTTONS];

			maths::vec2 m_mousePosition;

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
			bool isKeyTyped(unsigned int keyCode) const;
			bool isMouseButtonPressed(unsigned int mouseButton) const;
			bool isMouseButtonClicked(unsigned int mouseButton) const;
			const maths::vec2& getMousePosition() const;
		private:
			bool init();
			friend void windowResize(GLFWwindow* window, int width, int height);
			friend void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
			friend void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
			friend void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
		};
	}
}
