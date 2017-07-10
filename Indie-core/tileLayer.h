#pragma once

#include "src/graphics/layers/layer.h"
#include "src/graphics/batchRenderer2d.h"


class TileLayer : public indie::graphics::Layer
{
public:
	TileLayer(indie::graphics::Shader* shader);
	~TileLayer();
};
