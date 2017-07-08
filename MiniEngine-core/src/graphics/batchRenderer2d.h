#pragma once

#include <cstddef>
#include "renderer2d.h"
#include "renderable2d.h"

#include "buffers/indexBuffer.h"


namespace MiniEngine
{
	namespace graphics
	{
//���ο���Ⱦ�������		
#define RENDERER_MAX_SPRITES   60000
//������Ⱦ�������
#define RENDERER_MAX_TEXTURES  32
//�������ݴ�С
#define RENDERER_VERTEX_SIZE   sizeof(VertexData)
//�����С�����ΰ����ĸ����㣩
#define RENDERER_SPRITE_SIZE   RENDERER_VERTEX_SIZE * 4
//��������С
#define RENDERER_BUFFER_SIZE   RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
//���������С
#define RENDERER_INDICES_SIZE  RENDERER_MAX_SPRITES * 6


#define SHADER_VERTEX_INDEX  0
#define SHADER_UV_INDEX      1
#define SHADER_TID_INDEX     2
#define SHADER_COLOR_INDEX   3

		class BatchRenderer2D : public Renderer2D
		{
		private:
			//vertex buffer object�������е�����Ⱦ�������Ϣ��position, color��
			GLuint m_vertexBufferObj;
			GLuint m_vertexArrayObj;//vertex array object
			IndexBuffer* m_pIndexBufferObj;
			VertexData* m_pBuffer;
			GLuint m_indexCnt;

			std::vector<GLuint> m_textureSlots;
		public:
			BatchRenderer2D();
			~BatchRenderer2D();

			void begin() override;
			void submit(const Renderable2D* renderable2d) override;
			void drawString(const std::string& text, const maths::vec3& position, const Font& font, unsigned int color) override;
			void end() override;
			void flush() override;
		private:
			void init();
		};
	}
}