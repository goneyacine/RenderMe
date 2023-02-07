#pragma once


namespace RenderMe
{

	namespace Base
	{
		class Texture
		{
		public :
			Texture();
			Texture(unsigned int p_width,unsigned int p_height,unsigned int p_textureGL);
			~Texture();
			inline unsigned int getWidth() const;
			inline unsigned int getHeight() const;
			inline unsigned int getGlTexture() const;
		private :
			unsigned int m_width;
			unsigned int m_height;
			unsigned int m_textureGL;
		};
	}

}