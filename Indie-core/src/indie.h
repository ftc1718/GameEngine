#pragma once

#ifdef INDIE_EMSCRIPTEN
	#include <emscripten/emscripten.h>
	#include <functional>
#endif

#include "graphics/window.h"
#include "graphics/batchRenderer2d.h"
#include "graphics/layers/layer.h"
#include "graphics/Sprite.h"
#include "graphics/label.h"
#include "utility/timer.h"

#ifdef INDIE_EMSCRIPTEN

static void dispatchMain(void* fp)
{
	std::function<void()>* func = (std::function<void()>*)fp;
	(*func)();
}

#endif // INDIE_EMSCRIPTEN



namespace indie
{
	class Indie
	{
	private:
		graphics::Window* m_pWindow;
		Timer* m_pTimer;
		unsigned int m_framesPerSecond;
		unsigned int m_updatesPerSecond;
	protected:
		Indie()
			: m_framesPerSecond(0), m_updatesPerSecond(0)
		{

		}

		virtual ~Indie()
		{
			delete m_pTimer;
			delete m_pWindow;
		}

		graphics::Window* createWindow(const char* name, int width, int height)
		{
			m_pWindow = new graphics::Window(name, width, height);
			return m_pWindow;
		}

		const unsigned int getFPS() const { return m_framesPerSecond; }
		const unsigned int getUPS() const { return m_updatesPerSecond; }//return 60

		virtual void init() = 0;

		//run once per second
		virtual void tick() = 0;

		//run 60 times per second
		virtual void update() = 0;

		virtual void render() = 0;
	public:
		void start()
		{
			init();
			run();
		}
	private:
		void run()
		{
			m_pTimer = new Timer();
			float framesTimer = 0.0f;
			float updatesTimer = 0.0f;
			float updateTick = 1.0f / 60.0f;
			unsigned int frames = 0;
			unsigned int updates = 0;

#ifdef INDIE_EMSCRIPTEN
			std::function<void()> mainloop = [&] {
#else
			while (!m_pWindow->closed())
			{
#endif
				m_pWindow->clear();

				if (m_pTimer->elapsed() - updatesTimer > updateTick)
				{
					update();
					updatesTimer += updateTick;
					updates++;
				}

				frames++;
				render();
				m_pWindow->update();

				if (m_pTimer->elapsed() - framesTimer > 1.0f)
				{
					framesTimer += 1.0f;
					m_framesPerSecond = frames;
					m_updatesPerSecond = updates;
					frames = 0;
					updates = 0;
					tick();
				}
#ifdef INDIE_EMSCRIPTEN
			};
			emscripten_set_main_loop_arg(dispatchMain, &mainloop, 0, 1);
#else
			}
#endif
		}
	};
}