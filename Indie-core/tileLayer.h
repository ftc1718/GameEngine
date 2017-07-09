#pragma once

#include "src/graphics/layers/layer.h"
#include "src/graphics/batchRenderer2d.h"


class TileLayer : public Indie::graphics::Layer
{
public:
	TileLayer(Indie::graphics::Shader* shader);
	~TileLayer();
};
