#pragma once
#include <cassert>
#include "GL/glew.h"



#define GL_CALL(x) RenderMe::Base::ClearGLErrors();\
 x;\
 assert(RenderMe::Base::LogGLErrors());

namespace RenderMe
{
	namespace Base

	{
		 void ClearGLErrors();
		 bool LogGLErrors();
	}
}