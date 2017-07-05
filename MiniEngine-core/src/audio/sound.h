#pragma once

#include <string>
#include "gorilla/ga.h"
#include "gorilla/gau.h"

namespace MiniEngine
{
	namespace audio
	{
		class Sound
		{
		private:
			ga_Sound* m_sound;
			ga_Handle* m_handle;
			gc_float32 m_volume;
			gau_SampleSourceLoop* m_loopSrc;
			gau_SampleSourceLoop** m_pLoopSrc;

			std::string m_soundName;
			std::string m_fileName;

			bool m_isPlaying;
		public:
			Sound(const std::string& soundName, const std::string& fileName);
			~Sound();

			void play(bool loop = false);
			void stop();
			void resume();
			void setVolume(gc_float32 volume);

			inline const gc_float32 getVolume() const { return m_volume; }
			inline const std::string getSoundName() const { return m_soundName; }
			inline const std::string getFileName() const { return m_fileName; }
		};
	}
}