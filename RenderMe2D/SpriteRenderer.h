#pragma once
#include <vector>
#include "Texture.h"
#include "Uniforms.h"

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

			void setPixelsPerUnit(unsigned int p_PPU);
			 unsigned int getPixelsPerUnit() const;

			inline std::vector<float> getVertices() const;
			inline std::vector<unsigned int> getIndices()const;

			void setTexture(RenderMe::Base::Texture p_texture);
			inline RenderMe::Base::Texture getTexture() const;


		private : 

			void computeVertices();
			std::vector<float> m_vertices;
			std::vector<unsigned int> m_indices = { 0, 1, 2, 2, 3, 0 };
			float m_color[4] = {0,0,0,1};
			RenderMe::Base::Texture m_texture;
			//PPU stands for pixels per unit
			unsigned int m_PPU = 100;

			unsigned int m_glProgramID = 0;

			//texture uniforms data
			std::vector<RenderMe::Base::Uniform1f> m_uniforms_1f;
			std::vector<RenderMe::Base::Uniform2f> m_uniforms_2f;
			std::vector<RenderMe::Base::Uniform3f> m_uniforms_3f;
			std::vector<RenderMe::Base::Uniform4f> m_uniforms_4f;


			std::vector<RenderMe::Base::Uniform1i> m_uniforms_1i;
			std::vector<RenderMe::Base::Uniform2i> m_uniforms_2i;
			std::vector<RenderMe::Base::Uniform3i> m_uniforms_3i;
			std::vector<RenderMe::Base::Uniform4i> m_uniforms_4i;

			std::vector<RenderMe::Base::Uniform1ui> m_uniforms_1ui;
			std::vector<RenderMe::Base::Uniform2ui> m_uniforms_2ui;
			std::vector<RenderMe::Base::Uniform3ui> m_uniforms_3ui;
			std::vector<RenderMe::Base::Uniform4ui> m_uniforms_4ui;
		};
	}
}