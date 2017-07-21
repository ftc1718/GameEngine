#include "textureManager.h"

namespace indie
{
	namespace graphics
	{
		std::vector<Texture*> TextureManager::m_texturesVector;

		void TextureManager::add(Texture* texture)
		{
			m_texturesVector.push_back(texture);
		}

		Texture* TextureManager::get()
		{
			return m_texturesVector[0];
		}

		Texture* TextureManager::get(const std::string& name)
		{
			for (Texture* texture : m_texturesVector)
			{
				if (texture->getTextureName() == name)
				{
					return texture;
				}
			}
			return nullptr;
		}

		void TextureManager::clean()
		{
			for (int i = 0; i != m_texturesVector.size(); ++i)
			{
				delete m_texturesVector[i];
			}
		}
	}
}