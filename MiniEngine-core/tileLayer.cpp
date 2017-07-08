#include "tileLayer.h"

TileLayer::TileLayer(MiniEngine::graphics::Shader* shader)
	: Layer(new MiniEngine::graphics::BatchRenderer2D(), shader, MiniEngine::maths::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f))
{

}

TileLayer::~TileLayer()
{

}