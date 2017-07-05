#include "soundManager.h"

namespace MiniEngine
{
	namespace audio
	{
		gau_Manager* SoundManager::m_manager = nullptr;
		ga_Mixer* SoundManager::m_mixer = nullptr;

		std::vector<Sound*> SoundManager::m_soundsVector;

		void SoundManager::init()
		{
			gc_initialize(0);
			m_manager = gau_manager_create();
			m_mixer = gau_manager_mixer(m_manager);
		}

		void SoundManager::add(Sound* Sound)
		{
			m_soundsVector.push_back(Sound);
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

		void SoundManager::update()
		{
			gau_manager_update(m_manager);
		}

		void SoundManager::clean()
		{
			for (int i = 0; i != m_soundsVector.size(); ++i)
			{
				delete m_soundsVector[i];
			}

			gau_manager_destroy(m_manager);
			gc_shutdown();
		}

	}
}