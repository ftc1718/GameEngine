#include "tileLayer.h"

TileLayer::TileLayer(indie::graphics::Shader* shader)
	: Layer(new indie::graphics::BatchRenderer2D(), shader, indie::maths::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f))
{

}

TileLayer::~TileLayer()
{

}