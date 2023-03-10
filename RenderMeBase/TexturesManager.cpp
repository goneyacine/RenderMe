#include "TexturesManager.h"
#include "stb_image.h"
#include "GL/glew.h"
#include "ErrorHandler.h"

using namespace RenderMe::Base;


TexturesManager::TexturesManager() 
{

}


TexturesManager::~TexturesManager()
{
	//deleting all the textures from the gpu
	unsigned int texture_id = 0;
	for (auto const& [key, val] : m_textures)
	{
		texture_id = val.getOpenGL_ID();
		glDeleteTextures(1,&texture_id);
	}
}


int TexturesManager::deleteTexture(std::string p_name)
{
	return 0;
}

int  TexturesManager::addTexture(std::string p_filePath, std::string p_name)
{

	//just loading the texture from the disk
	stbi_set_flip_vertically_on_load(1);
	int width = 0;
	int height = 0;
	int BPP = 0;
	unsigned char* temp_buffer = stbi_load(p_filePath.c_str(), &width, &height,&BPP,4);
	//the opengl stuff 
	unsigned int textureGL;
	GL_CALL(glEnable(GL_TEXTURE_2D))
	GL_CALL(glGenTextures(1, &textureGL))
	GL_CALL(glBindTexture(GL_TEXTURE_2D, textureGL))

	//Setup wrap mode
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE))
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE))

	//Setup texture scaling filtering
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR))
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR))


	GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,width,height, 0, GL_RGBA, GL_UNSIGNED_BYTE, temp_buffer))

	GL_CALL(glBindTexture(GL_TEXTURE_2D,0))
	//adding the new texture to the textures map
	m_textures[p_name] = Texture((unsigned int)width,(unsigned int)height,textureGL);

	if (temp_buffer)
		stbi_image_free(temp_buffer);

	return 0;
}

int  TexturesManager::addTexture(unsigned char* p_data, unsigned int p_width, unsigned int p_height, std::string p_name)
{
	//the opengl stuff 
	unsigned int textureGL;
	GL_CALL(glEnable(GL_TEXTURE_2D))
	GL_CALL(glGenTextures(1, &textureGL))
	GL_CALL(glBindTexture(GL_TEXTURE_2D, textureGL))

	//Setup wrap mode
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE))
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE))

	//Setup texture scaling filtering
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR))
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR))


	GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, p_width, p_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, p_data))

	GL_CALL(glBindTexture(GL_TEXTURE_2D, 0))
	//adding the new texture to the textures map
	m_textures[p_name] = Texture((unsigned int)p_width,(unsigned int)p_height,textureGL);

	return 0;
}


 Texture TexturesManager::getTexture(std::string p_name) 
{
	return m_textures[p_name];
}