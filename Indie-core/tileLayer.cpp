#include "tileLayer.h"

TileLayer::TileLayer(Indie::graphics::Shader* shader)
	: Layer(new Indie::graphics::BatchRenderer2D(), shader, Indie::maths::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f))
{

}

TileLayer::~TileLayer()
{

}