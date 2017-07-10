#include "game.h"

Game::Game()
{

}

Game::~Game()
{
	/*
	  BatchRender2D, m_pShader and rendererable(m_pSprite and m_pLabel)
	  delete in ~Layer()
	*/
	delete m_pLayer;
}

void Game::init()
{
	m_pWindow = createWindow("Test Game", 960, 540);
	m_pShader = new Shader("src/shaders/vertexShader.shader", "src/shaders/fragmentShader.shader");
	m_pLayer = new Layer(new BatchRenderer2D(), m_pShader, maths::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));
	FontManager::get()->setScale(m_pWindow->getWidth() / 32.0f, m_pWindow->getHeight() / 18.0f);
	m_pSprite = new Sprite(1.0f, 1.0f, 4, 4, new Texture("test2.png"));
	m_pLayer->add(m_pSprite);

	m_pLabel = new Label("", -15.5f, 7.5f, 0xffffffff);
	m_pLayer->add(m_pLabel);
}

void Game::tick()
{
	m_pLabel->m_text = std::to_string(getFPS()) + "fps";
	std::cout << getUPS() << "ups, " << getFPS() << "fps" << std::endl;
}

void Game::update()
{
	float speed = 0.5f;
	maths::vec3 position = m_pSprite->getPosition();

	if (m_pWindow->isKeyPressed(GLFW_KEY_UP))
	{
		position.y += speed;
		m_pSprite->setPosition(position);
	}

	else if (m_pWindow->isKeyPressed(GLFW_KEY_DOWN))
	{
		position.y -= speed;
		m_pSprite->setPosition(position);
	}
	
	if (m_pWindow->isKeyPressed(GLFW_KEY_LEFT))
	{
		position.x -= speed; 
		m_pSprite->setPosition(position);
	}
	
	else if (m_pWindow->isKeyPressed(GLFW_KEY_RIGHT))
	{
		position.x += speed;
		m_pSprite->setPosition(position);
	}

	double x, y;
	m_pWindow->getMousePosition(x, y);
	m_pShader->setUniform2f("lightPosition", maths::vec2((float)(x * 32.0f / m_pWindow->getWidth() - 16.0f), (float)(9.0f - y * 18.0f / m_pWindow->getHeight())));
}

void Game::render()
{
	m_pLayer->render();
}