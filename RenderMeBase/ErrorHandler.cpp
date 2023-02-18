#include <iostream>
#include "ErrorHandler.h"
 void RenderMe::Base::ClearGLErrors()
{
	while (glGetError() != GL_NO_ERROR);
}

 bool RenderMe::Base::LogGLErrors()
{
	while (GLenum error = glGetError())
	{
		std::cout << "\n [OPENGL ERROR MESSAGE] " << error << "\n";
		return false;
	}
	return true;
}