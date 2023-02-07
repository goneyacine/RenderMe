#include "ShadersManager.h"
#include <GL/glew.h>
#include <fstream>
#include <string>
using namespace RenderMe::Base;


ShaderManager::ShaderManager()
{

}


ShaderManager::~ShaderManager()
{
    for (auto const& [key, val] : m_shaders)
    {
        glDeleteShader(val.first);
    }
}


int ShaderManager::compileShader(char* p_compileMessage,std::string p_shaderName, GLenum p_shaderType,std::string p_filePath)
{
	unsigned int shader = glCreateShader(p_shaderType);
    //remeber to delete this after passing the source to opengl
    char* source;
	//reading shader's source from source file
    std::ifstream sourceFile(p_filePath);

    if (sourceFile.is_open())
    {
    std::string temp_source;
    std::string temp_line;
        while (sourceFile.good())
        {
            std::getline(sourceFile,temp_line);
            temp_source += temp_line;
        }
        source = new char[temp_source.length() + 1];
        strcpy_s(source,sizeof(source), temp_source.c_str());
    }

    //you can delete this if you want
    sourceFile.close();

	glShaderSource(shader, 1, &source, nullptr);
    delete[] source;
    glCompileShader(shader);
    
	int result;


    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

    //if the compiling process faild 
    if (!result)
    {
        int length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

        p_compileMessage = (char*)malloc(length * sizeof(char));

        glGetShaderInfoLog(shader, length, &length, p_compileMessage);
        //here we are deleting the shader because the compiling process failed so there is no need for it 
        glDeleteShader(shader);
        return -1;
    }

    //assigning shader's name and object to the map
    m_shaders[p_shaderName] = std::pair<unsigned int,GLenum>(shader,p_shaderType);

	return 0;
}