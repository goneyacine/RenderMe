#pragma once
#include <string>

namespace RenderMe
{
	namespace Base
	{
		struct Uniform1f
		{
			std::string name;
			float value1;
		};

		struct Uniform2f
		{
			std::string name;
			float value1;
			float value2;
		};

		struct Uniform3f
		{
			std::string name;
			float value1;
			float value2;
			float value3;

		};

		struct Uniform4f
		{
			std::string name;
			float value1;
			float value2;
			float value3;
			float value4;
		};

		struct Uniform1i
		{
			std::string name;
			int value1;
		};


		struct Uniform2i
		{
			std::string name;
			int value1;
			int value2;
        };

		struct Uniform3i
		{
			std::string name;
			int value1;
			int value2;
			int value3;
		};

		struct Uniform4i
		{
			std::string name;
			int value1;
			int value2;
			int value3;
			int value4;
		};


		struct Uniform1ui
		{
			std::string name;
			unsigned int value1;
		};

		struct Uniform2ui
		{
			std::string name;
			unsigned int value1;
			unsigned int value2;
		};

		struct Uniform3ui
		{
			std::string name;
			unsigned int value1;
			unsigned int value2;
			unsigned int value3;

		};

		struct Uniform4ui
		{
			std::string name;
			unsigned int value1;
			unsigned int value2;
			unsigned int value3;
			unsigned int value4;
		};


	}
}