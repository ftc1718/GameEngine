#include "label.h"

namespace MiniEngine
{
	namespace graphics
	{
		Label::Label(const std::string& text, float x, float y, maths::vec4 color)
			: Renderable2D(maths::vec3(x, y, 0.0f), maths::vec2(), color), m_text(text)
		{

		}

		void Label::submit(Renderer2D* renderer) const
		{
			renderer->drawString(m_text, m_position, m_color);
		}
	}
}