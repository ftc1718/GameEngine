#include "sound.h"
#include "soundManager.h"
#include "../utility/stringUtils.h"
#include "../utility/log.h"
#include <iostream>

namespace indie
{
	namespace audio
	{
#ifndef INDIE_EMSCRIPTEN
		static void setFlagAndDestroyOnFinish(ga_Handle* in_handle, void* in_context);
#endif

		Sound::Sound(const std::string& soundName, const std::string& fileName)
			: m_soundName(soundName), m_fileName(fileName), m_isPlaying(false)
		{

#ifndef INDIE_EMSCRIPTEN
			m_loopSrc = nullptr;
			m_pLoopSrc = &m_loopSrc;
#endif

			std::vector<std::string> split = splitString(m_fileName, '.');

			if (split.size() < 2)
			{
				std::cout << "Invalid file name!" << std::endl;
				return;
			}

#ifndef INDIE_EMSCRIPTEN

			m_sound = gau_load_sound_file(m_fileName.c_str(), split.back().c_str());

			INDIE_ASSERT(m_sound, "Cound not load sound file!");

#endif

		}

		Sound::~Sound()
		{
#ifndef INDIE_EMSCRIPTEN
			if (m_sound != nullptr)
			{
				ga_sound_release(m_sound);
			}
#endif
		}


		void Sound::play(bool loop)
		{
#ifdef INDIE_EMSCRIPTEN
			SoundManagerPlay(m_soundName.c_str());
#else
			if (!loop)
				m_pLoopSrc = nullptr;
			m_handle = gau_create_handle_sound(SoundManager::m_mixer, m_sound, &setFlagAndDestroyOnFinish, NULL, m_pLoopSrc);
			ga_handle_play(m_handle);
#endif
			m_isPlaying = true;
		}

		void Sound::loop()
		{
#ifdef INDIE_EMSCRIPTEN
			SoundManagerLoop(m_soundName.c_str());
#else
			play(true);
#endif
		}

		void Sound::stop()
		{
			if (!m_isPlaying)
			{
				return;
			}
#ifdef INDIE_EMSCRIPTEN
			SoundManagerStop(m_soundName.c_str());
#else

			ga_handle_stop(m_handle);
#endif
			m_isPlaying = false;
		}

		void Sound::pause()
		{
#ifdef INDIE_EMSCRIPTEN
			SoundManagerPause(m_soundName.c_str());
#else
			stop();
#endif
		}

		void Sound::resume()
		{
			if (m_isPlaying)
			{
				return;
			}
#ifdef INDIE_EMSCRIPTEN
			SoundManagerPlay(m_soundName.c_str());
#else

			ga_handle_play(m_handle);
#endif
			m_isPlaying = true;
		}

		void Sound::setVolume(float volume)
		{
			if (!m_isPlaying)
			{
				std::cout << "No sound playing now!" << std::endl;
				return;
			}
			m_volume = volume;

#ifdef INDIE_EMSCRIPTEN
			SoundManagerSetVolume(m_soundName.c_str(), volume);
#else
			ga_handle_setParamf(m_handle, GA_HANDLE_PARAM_GAIN, m_volume);
#endif
		}

#ifndef INDIE_EMSCRIPTEN
		void setFlagAndDestroyOnFinish(ga_Handle* in_handle, void* in_context)
		{
			ga_handle_destroy(in_handle);
		}
#endif

	}
}