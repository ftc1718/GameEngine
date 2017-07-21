#pragma once

#pragma once

#include <vector>
#include "texture.h"

namespace indie
{
	namespace graphics
	{
		class TextureManager
		{
		private:
			static std::vector<Texture*> m_texturesVector;
		public:
			static void add(Texture* texture);
			static Texture* get();
			static Texture* get(const std::string& name);
			static void clean();
		private:
			TextureManager() { }
		};
	}
}