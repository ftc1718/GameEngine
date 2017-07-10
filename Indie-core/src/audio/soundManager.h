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
			static gau_Manager* m_manager;
			static ga_Mixer* m_mixer;
			static std::vector<Sound*> m_soundsVector;
		public:
			static void init();
			static void add(Sound* Sound);
			static Sound* get(const std::string& name);
			static void update();
			static void clean();
		private:
			SoundManager() { }
		};
	}
}