#pragma once

#include <vector>
#include "sound.h"

namespace indie
{
	namespace audio
	{
		class SoundManager
		{
			friend class Sound;
		private:
#ifndef INDIE_EMSCRIPTEN
			static gau_Manager* m_manager;
			static ga_Mixer* m_mixer;
#endif
			static std::vector<Sound*> m_soundsVector;
		public:
			static void init();
			static void add(Sound* sound);
			static Sound* get(const std::string& name);
#ifndef INDIE_EMSCRIPTEN
			static void update();
#endif
			static void clean();
		private:
			SoundManager() { }
		};
	}
}