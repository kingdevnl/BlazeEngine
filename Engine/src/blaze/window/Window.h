#pragma once
#include <string>

typedef struct GLFWwindow GLFWwindow;

namespace Blaze
{
	class Window
	{

	public:
		int width = 1080, height = 720;
		void Create(std::string name);
		GLFWwindow* handle;
	};
}
