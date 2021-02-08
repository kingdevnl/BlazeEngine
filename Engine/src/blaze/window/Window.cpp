#include "Window.h"
#include "../Core.h"
#include "../app/App.h"

namespace Blaze
{


	void OnResize(GLFWwindow* handle, int w, int h)
	{
		if(w >= 0 && h >= 0)
		{
			auto window = App::GetApp()->window;
			window->width = w;
			window->height = h;
		}
		
	}
	
	

	void Window::Create(std::string name)
	{
		if(glfwInit() == GLFW_FALSE)
		{
			spdlog::error("GLFW Error");
			throw std::exception("GLFW Error");
		}
		glfwDefaultWindowHints();

		handle = glfwCreateWindow(width, height,name.c_str(), 0, 0);
		glfwMakeContextCurrent(handle);
		if(glewInit() != GLEW_OK)
		{
			spdlog::error("GLEW Error");
			throw std::exception("GLEW Error");
		}
		glfwSwapInterval(1);

		glfwSetWindowSizeCallback(handle, OnResize);
		

	}
}
