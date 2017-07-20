#pragma once

#include <vector>
#include "sound.h"

#ifdef INDIE_EMSCRIPTEN
//implememnt C api in JS
extern "C"
{
	void SoundManagerAdd(const char* name, const char* fileName);
	void SoundManagerPlay(const char* name);
	void SoundManagerPause(const char* name);
	void SoundManagerStop(const char* name);
	void SoundManagerLoop(const char* name);
	void SoundManagerSetVolume(const char* name, double volume);
}
#endif

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
			static Sound* add(Sound* sound);
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