#include "soundManager.h"

namespace indie
{
	namespace audio
	{
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
#else
		gau_Manager* SoundManager::m_manager = nullptr;
		ga_Mixer* SoundManager::m_mixer = nullptr;
#endif

		std::vector<Sound*> SoundManager::m_soundsVector;

		void SoundManager::init()
		{
#ifdef INDIE_EMSCRIPTEN
			EM_ASM(
			Module.SoundManager = {};
			Module.SoundManager.m_sounds = {};
			Module.SoundManagerAdd = function(name, fileName) { alert('Loading audio file ' + name + ' path = ' fileName + '!'); Module.SoundManager.m_sounds[name] = new Audio(fileName); };
			Module.SoundManagerPlay = function(name) { Module.SoundManager.m_sounds[name].play(); };
			Module.SoundManagerPause = function(name) { Module.SoundManager.m_sounds[name].pause(); };
			Module.SoundManagerStop = function(name) { Module.SoundManager.m_sounds[name].pause(); Module.SoundManager.m_sounds[name].currentTime = 0;  Module.SoundManager.m_sounds[name].loop = false; };
			Module.SoundManagerLoop = function(name) { Module.SoundManager.m_sounds[name].play(); Module.SoundManager.m_sounds[name].loop = true; };
			Module.SoundManagerSetVolume = function(name, volume) { Module.SoundManager.m_sounds[name].volume = volume; };
			);
#else
			gc_initialize(0);
			m_manager = gau_manager_create();
			m_mixer = gau_manager_mixer(m_manager);
#endif
		}

		void SoundManager::add(Sound* sound)
		{
			m_soundsVector.push_back(sound);

#ifdef INDIE_EMSCRIPTEN
			SoundManagerAdd(sound->getSoundName().c_str(), sound->getFileName().c_str());
#endif
		}
		
		Sound* SoundManager::get(const std::string& name)
		{
			for (Sound* sound : m_soundsVector)
			{
				if (sound->getSoundName() == name)
				{
					return sound;
				}
			}
			return nullptr;
		}

#ifndef INDIE_EMSCRIPTEN
		void SoundManager::update()
		{
			gau_manager_update(m_manager);
		}
#endif

		void SoundManager::clean()
		{
			for (int i = 0; i != m_soundsVector.size(); ++i)
			{
				delete m_soundsVector[i];
			}

#ifndef INDIE_EMSCRIPTEN
			gau_manager_destroy(m_manager);
			gc_shutdown();
#endif
		}

	}
}