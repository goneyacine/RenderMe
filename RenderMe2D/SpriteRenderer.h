#pragma once
#include <vector>
#include "Texture.h"

namespace RenderMe
{
	namespace RenderMe2D
	{
		class SpriteRenderer
		{
		public :
			SpriteRenderer();
			SpriteRenderer(RenderMe::Base::Texture p_texture);
			//PPU stands for pixels per unit (default value is 100)
			SpriteRenderer(RenderMe::Base::Texture p_texture, unsigned int p_PPU = 100);
			//PPU stands for pixels per unit (default value) + the color should be in RGBA format and should be normalized(between 0 and 1)
			SpriteRenderer(RenderMe::Base::Texture p_texture,float* p_color, unsigned int p_PPU = 100);
			~SpriteRenderer();

			void setPixelsPerUnit(unsigned int p_PPU);
			inline unsigned int getPixelsPerUnit() const;

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
		};
	}
}