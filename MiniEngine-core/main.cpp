#if 0
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
#include "src/graphics/layers/group.h"

#include "src/graphics/texture.h"
#include "src/graphics/label.h"

#include "src/graphics/fontManager.h"



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
	Shader& shader = *s;


	GLint texIDs[] =
	{
		0,1,2,3,4,5,6,7,8,9
	};

	shader.enable();
	shader.setUniform1iv("textures", texIDs, 10);

	Texture* textures[] =
	{
		new Texture("test.png"),
		new Texture("test2.png"),
		new Texture("test3.png")

	};

	TileLayer layer(&shader);
	for (float y = -9.0f; y < 9.0f; y++)
	{
		for (float x = -16.0f; x < 16.0f; x++)
		{
			//layer.add(new Sprite(x, y, 0.9f, 0.9f, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
			int r = rand() % 256;
			//0xff(a)ff(b)ff(g)ff(r)
			int col = 0xffff0000 | r;
			if (rand() % 4 == 0)
			{
				layer.add(new Sprite(x, y, 0.9f, 0.9f, col));
				//delete Sprite in ~Layer()
			}
			else
			{
				layer.add(new Sprite(x, y, 0.9f, 0.9f, textures[rand() % 3]));
				//delete Sprite in ~Layer()
			}
		}
	}

//	FontManager::add(new Font("SourceSansPro", "SourceSansPro-Light.ttf", 50));
	Group* g = new Group(maths::mat4::translate(maths::vec3(-15.5f, 7.5f, 0.0f)));
//	Label* fps = new Label("", -15, 8, maths::vec4(1, 1, 1, 1));
	Label* fps = new Label("", 0.5f, 0.5f, 0xffffffff);
	g->add(new Sprite(0, 0, 4, 1.5f, 0x505050DD));
	g->add(fps);

	layer.add(g);

	Timer timer;
	double time = 0;
	unsigned int frames = 0;
	float t = 0.0f;
	while (!window.closed())
	{
		t += 0.01f;
		window.clear();
		double x, y;
		window.getMousePosition(x, y);
		shader.enable();
		shader.setUniform2f("lightPosition", vec2((float)(x * 32.0f / window.getWidth() - 16.0f), (float)(9.0f - y * 18.0f / window.getHeight())));

		layer.render();

		const std::vector<Renderable2D*> renderables = layer.getRenderables();
		for (int i = 0; i != renderables.size(); ++i)
		{
			float c = sin(t) / 2 + 0.5f;
			renderables[i]->setColor(maths::vec4(c, 0, 1, 1));
		}

		window.update();
		frames++;
		if (timer.elapsed() - time > 1.0f)
		{
			time += 1.0f;
			fps->m_text = std::to_string(frames) + "fps";
			printf("%d fps\n", frames);
			frames = 0;
		}
	}

	for (int i = 0; i < 3; ++i)
	{
		delete textures[i];
	}

	return 0;
}
#endif

#include "gorilla/ga.h"
#include "gorilla/gau.h"

#include <stdio.h>

static void setFlagAndDestroyOnFinish(ga_Handle* in_handle, void* in_context)
{
	gc_int32* flag = (gc_int32*)(in_context);
	*flag = 1;
	ga_handle_destroy(in_handle);
}
int main(int argc, char** argv)
{
	gau_Manager* mgr;
	ga_Mixer* mixer;
	ga_Sound* sound;
	ga_Handle* handle;
	gau_SampleSourceLoop* loopSrc = 0;
	gau_SampleSourceLoop** pLoopSrc = &loopSrc;
	gc_int32 loop = 0;
	gc_int32 quit = 0;

	/* Initialize library + manager */
	gc_initialize(0);
	mgr = gau_manager_create();
	mixer = gau_manager_mixer(mgr);

	/* Create and play shared sound */
	if (!loop)
		pLoopSrc = 0;
	sound = gau_load_sound_file("test.wav", "wav");
	handle = gau_create_handle_sound(mixer, sound, &setFlagAndDestroyOnFinish, &quit, pLoopSrc);
	ga_handle_play(handle);

	/* Bounded mix/queue/dispatch loop */
	while (!quit)
	{
		gau_manager_update(mgr);
		printf("%d / %d\n", ga_handle_tell(handle, GA_TELL_PARAM_CURRENT), ga_handle_tell(handle, GA_TELL_PARAM_TOTAL));
		gc_thread_sleep(1);
	}

	/* Clean up sound */
	ga_sound_release(sound);

	/* Clean up library + manager */
	gau_manager_destroy(mgr);
	gc_shutdown();

	return 0;
}

