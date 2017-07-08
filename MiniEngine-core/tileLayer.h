#pragma once

#include "src/graphics/layers/layer.h"
#include "src/graphics/batchRenderer2d.h"


class TileLayer : public MiniEngine::graphics::Layer
{
public:
	TileLayer(MiniEngine::graphics::Shader* shader);
	~TileLayer();
};
