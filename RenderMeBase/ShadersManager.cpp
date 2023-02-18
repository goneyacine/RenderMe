#include <GL/glew.h>
#include <fstream>
#include <string>
#include "ShadersManager.h"
#include "ErrorHandler.h"
using namespace RenderMe::Base;


ShaderManager::ShaderManager()
{

}


ShaderManager::~ShaderManager()
{
    
    for (auto const& [key, val] : m_shaders)
    {
        GL_CALL(glDeleteShader(val.first))
    }

}


unsigned int ShaderManager::compileShader_by_filePath(std::string p_shaderName, GLenum p_shaderType,std::string p_filePath)
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
            temp_source += "\n";
        }
 
        source = new char[temp_source.length() + 1];
      strcpy_s(source, temp_source.length() + 1, temp_source.c_str());
    }
    else
    {
        return -1;
    }

    //you can delete this if you want
    sourceFile.close();

	GL_CALL(glShaderSource(shader, 1, &source, nullptr))
    //std::cout << source;
    delete[] source;
    GL_CALL(glCompileShader(shader))
    
	int result;


    GL_CALL(glGetShaderiv(shader, GL_COMPILE_STATUS, &result))

    //if the compiling process faild 
    if (!result)
    {
        char* compileMessage;
        int length;
        GL_CALL(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length))

        compileMessage = (char*)malloc(length * sizeof(char) + 1);

        GL_CALL(glGetShaderInfoLog(shader, length, &length, compileMessage))
        std::cout << compileMessage;
        //here we are deleting the shader because the compiling process failed so there is no need for it 

        GL_CALL(glDeleteShader(shader))
        return 0;
    }

    //assigning shader's name and object to the map
    m_shaders[p_shaderName] = std::pair<unsigned int,GLenum>(shader,p_shaderType);
 
	return shader;
  
}


unsigned int ShaderManager::compileShader_by_source(std::string p_shaderName, GLenum p_shaderType, std::string p_source)
{


    unsigned int shader = glCreateShader(p_shaderType);
    //remeber to delete this after passing the source to opengl
    char* source = new char[p_source.length() + 1];
    strcpy_s(source, p_source.length() + 1, p_source.c_str());


   
    GL_CALL(glShaderSource(shader, 1, &source, nullptr))
    delete[] source;
    GL_CALL(glCompileShader(shader))

    int result;


    GL_CALL(glGetShaderiv(shader, GL_COMPILE_STATUS, &result))

    //if the compiling process faild 
    if (!result)
    {
        char* compileMessage;
        int length;
        GL_CALL(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length))

        compileMessage = (char*)malloc(length * sizeof(char) + 1);

        GL_CALL(glGetShaderInfoLog(shader, length, &length, compileMessage))
        std::cout << compileMessage;
        //here we are deleting the shader because the compiling process failed so there is no need for it 

        GL_CALL(glDeleteShader(shader))
        return 0;
    }

    //assigning shader's name and object to the map
    m_shaders[p_shaderName] = std::pair<unsigned int, GLenum>(shader, p_shaderType);

    return shader;

}