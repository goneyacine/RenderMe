#pragma once
#include <vector>
#include "Texture.h"
#include "Uniforms.h"
#include "Vertex.h"

namespace RenderMe
{
	namespace RenderMe2D
	{
		class SpriteRenderer
		{
		public :			
			SpriteRenderer();
			SpriteRenderer(RenderMe::Base::Texture p_texture, unsigned int p_vertexShader,unsigned int p_fragementShaderID);
			//PPU stands for pixels per unit (default value is 100)
			SpriteRenderer(RenderMe::Base::Texture p_texture, unsigned int p_vertexShaderID,unsigned int p_fragmentShaderID,unsigned int p_PPU = 100);
			//PPU stands for pixels per unit (default value) + the color should be in RGBA format and should be normalized(between 0 and 1)
			SpriteRenderer(RenderMe::Base::Texture p_texture,float* p_color, unsigned int p_vertexShaderID, unsigned int p_fragmentShaderID, unsigned int p_PPU = 100);
			~SpriteRenderer();

			RenderMe::Base::Texture getTexture() const;
			unsigned int getShaderProgram() const;
			void setTexture(RenderMe::Base::Texture p_texture);



			//texture uniforms data
			std::vector<RenderMe::Base::Uniform1f> g_uniforms_1f;
			std::vector<RenderMe::Base::Uniform2f> g_uniforms_2f;
			std::vector<RenderMe::Base::Uniform3f> g_uniforms_3f;
			std::vector<RenderMe::Base::Uniform4f> g_uniforms_4f;


			std::vector<RenderMe::Base::Uniform1i> g_uniforms_1i;
			std::vector<RenderMe::Base::Uniform2i> g_uniforms_2i;
			std::vector<RenderMe::Base::Uniform3i> g_uniforms_3i;
			std::vector<RenderMe::Base::Uniform4i> g_uniforms_4i;

			std::vector<RenderMe::Base::Uniform1ui> g_uniforms_1ui;
			std::vector<RenderMe::Base::Uniform2ui> g_uniforms_2ui;
			std::vector<RenderMe::Base::Uniform3ui> g_uniforms_3ui;
			std::vector<RenderMe::Base::Uniform4ui> g_uniforms_4ui;


			float g_color[4] = {0,0,0,1};
			//PPU stands for pixels per unit
			unsigned int g_PPU = 100;
		private : 

			RenderMe::Base::Texture m_texture;
			

			unsigned int m_glProgramID = 0;

		};
	}
}