#pragma once

#include <unordered_map>
#include <string>

#include "Texture.h"

namespace RenderMe
{
	namespace Base
	{
		class TexturesManager
		{
		public :
			TexturesManager();
			~TexturesManager();
			int deleteTexture(std::string p_name);
			//addding texture by passing the file path
			int addTexture(std::string p_filePath,std::string p_name);
			//adding texture by passing data directly 
			int addTexture(unsigned char* p_data,unsigned int p_width,unsigned int p_hieght,std::string p_name);

			 Texture getTexture(std::string p_name);
		private :
			//a map that assigns texture name (key) with its  texture object (value)
			std::unordered_map<std::string, Texture> m_textures;
		};
	}
}
