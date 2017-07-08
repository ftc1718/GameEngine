#include "sound.h"
#include "soundManager.h"
#include "../utility/stringUtils.h"
#include <iostream>

namespace MiniEngine
{
	namespace audio
	{
		static void setFlagAndDestroyOnFinish(ga_Handle* in_handle, void* in_context);

		Sound::Sound(const std::string& soundName, const std::string& fileName)
			: m_soundName(soundName), m_fileName(fileName), m_isPlaying(false)
		{
			m_loopSrc = nullptr;
			m_pLoopSrc = &m_loopSrc;

			std::vector<std::string> split = splitString(m_fileName, '.');

			if (split.size() < 2)
			{
				std::cout << "Invalid file name!" << std::endl;
				return;
			}

			m_sound = gau_load_sound_file(m_fileName.c_str(), split.back().c_str());

			if (m_sound == nullptr)
			{
				std::cout << "Could not load sound file!" << std::endl;
			}
		}

		Sound::~Sound()
		{
			ga_sound_release(m_sound);
		}

		void Sound::play(bool loop)
		{
			if (!loop)
				m_pLoopSrc = nullptr;
			m_handle = gau_create_handle_sound(SoundManager::m_mixer, m_sound, &setFlagAndDestroyOnFinish, NULL, m_pLoopSrc);
			ga_handle_play(m_handle);
			m_isPlaying = true;
		}

		void Sound::stop()
		{
			if (!m_isPlaying)
			{
				return;
			}

			ga_handle_stop(m_handle);
			m_isPlaying = false;
		}

		void Sound::resume()
		{
			if (m_isPlaying)
			{
				return;
			}

			ga_handle_play(m_handle);
			m_isPlaying = true;
		}

		void Sound::setVolume(gc_float32 volume)
		{
			if (!m_isPlaying)
			{
				std::cout << "No sound playing now!" << std::endl;
				return;
			}

			m_volume = volume;
			ga_handle_setParamf(m_handle, GA_HANDLE_PARAM_GAIN, m_volume);
		}

		void setFlagAndDestroyOnFinish(ga_Handle* in_handle, void* in_context)
		{
			ga_handle_destroy(in_handle);
		}

	}
}