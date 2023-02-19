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




			void setUniforms_1f(RenderMe::Base::Uniform1f p_uniform);
			void setUniforms_2f(RenderMe::Base::Uniform2f p_uniform);
			void setUniforms_3f(RenderMe::Base::Uniform3f p_uniform);
			void setUniforms_4f(RenderMe::Base::Uniform4f p_uniform);

			void setUniforms_1i(RenderMe::Base::Uniform1i p_uniform);
			void setUniforms_2i(RenderMe::Base::Uniform2i p_uniform);
			void setUniforms_3i(RenderMe::Base::Uniform3i p_uniform);
			void setUniforms_4i(RenderMe::Base::Uniform4i p_uniform);

			void setUniforms_1ui(RenderMe::Base::Uniform1ui p_uniform);
			void setUniforms_2ui(RenderMe::Base::Uniform2ui p_uniform);
			void setUniforms_3ui(RenderMe::Base::Uniform3ui p_uniform);
			void setUniforms_4ui(RenderMe::Base::Uniform4ui p_uniform);


			


			float g_color[4] = {0,0,0,1};
			//PPU stands for pixels per unit
			unsigned int g_PPU = 100;
		private : 

			RenderMe::Base::Texture m_texture;
			

			unsigned int m_glProgramID = 0;

		};
	}
}