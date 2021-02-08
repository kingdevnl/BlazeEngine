#include "App.h"
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include "../Blaze.h"
#include "../window/Window.h"
#include "../render/layer/Layer.h"

namespace Blaze
{
	App* App::app = nullptr;

	App::App(std::string name)
	{
		this->name = name;
		this->window = std::make_shared<Window>();
		this->currentScene = std::make_shared<Scene>();
		app = this;
	}

	App* App::GetApp()
	{
		return app;
	}

	void App::PushLayer(Layer* layer)
	{
		this->layers.push_back(layer);
	}

	void App::Setup()
	{
		window->Create(this->name);
		
		for (auto* layer : layers)
		{
			layer->Setup();
		}

		currentScene->Setup();

		Run();
	}

	void App::Run()
	{
		float beginTime = static_cast<float>(glfwGetTime());
		float endTime = 0.f;
		float dt = -1.0f;
		
		while (!glfwWindowShouldClose(window->handle))
		{
			glfwPollEvents();

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glViewport(0, 0, window->width, window->height);
			
			for (auto layer : layers)
			{
				if (dt >= 0)
				{
					layer->OnUpdate(dt);
				}
				layer->OnRender();
			}


			glfwSwapBuffers(window->handle);
			endTime = static_cast<float>(glfwGetTime());
			dt = endTime - beginTime;
			beginTime = endTime;
		}
		Destroy();
	}


	void App::Destroy()
	{
		for (auto layer : layers)
		{
			layer->OnDestroy();
		}
		currentScene->OnDestroy();
	}
}

int main(int argc, char* argv[])
{
	Blaze::Setup();
	Blaze::App* app = Blaze::CreateApp();


	app->Setup();
}
