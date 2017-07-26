#pragma once

#include <indie.h>

using namespace indie;
using namespace graphics;

class Game : public Indie
{
private:
	Window* m_pWindow;
	Layer* m_pLayer;
	Label* m_pLabel;
	Sprite* m_pSprite;
	Shader* m_pShader;
public:
	Game();
	~Game();

	void init() override;
	void tick() override;
	void update() override;
	void render() override;
};