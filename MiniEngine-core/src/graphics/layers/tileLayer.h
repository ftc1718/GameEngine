#pragma once

#include "layer.h"
#include "../batchRenderer2d.h"

namespace MiniEngine
{
	namespace graphics
	{
		class TileLayer : public Layer
		{
		public:
			TileLayer(Shader* shader);
			~TileLayer();
		};
	}
}