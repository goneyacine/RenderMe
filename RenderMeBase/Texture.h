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
			unsigned int getWidth() const;
			unsigned int getHeight() const;
			unsigned int getOpenGL_ID() const;
		private :
			unsigned int m_width;
			unsigned int m_height;
			unsigned int m_textureGL;
		};
	}

}