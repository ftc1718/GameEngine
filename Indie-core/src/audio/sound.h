#pragma once

#include <string>

#ifdef INDIE_EMSCRIPTEN
	#include <emscripten/emscripten.h>
#else
	#include "gorilla/ga.h"
	#include "gorilla/gau.h"
#endif

namespace indie
{
	namespace audio
	{
		class Sound
		{
		private:

#ifndef INDIE_EMSCRIPTEN
			ga_Sound* m_sound;
			ga_Handle* m_handle;
			gau_SampleSourceLoop* m_loopSrc;
			gau_SampleSourceLoop** m_pLoopSrc;
#endif
			float m_volume;
			bool m_isPlaying;

			std::string m_soundName;
			std::string m_fileName;
		public:
			Sound(const std::string& soundName, const std::string& fileName);
			~Sound();

			void play(bool loop = false);
			void loop();
			void stop();
			void pause();
			void resume();
			void setVolume(float volume);

			inline const std::string getSoundName() const { return m_soundName; }
			inline const std::string getFileName() const { return m_fileName; }
			inline const float getVolume() const { return m_volume; }
		};
	}
}