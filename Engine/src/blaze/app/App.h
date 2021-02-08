#pragma once
#include "../scene/Scene.h"
#include "../window/Window.h"

int main(int argc, char* argv[]);



namespace Blaze
{
	class Layer;

	// class Window;
	class App
	{
	public:
		App(const std::string name);
		std::shared_ptr<Window> window;
		std::shared_ptr<Scene> currentScene = nullptr;
		static App* GetApp();
		
	protected:
		void PushLayer(Layer* layer);
		virtual void Destroy();
		virtual void Setup();
		std::string name;

		
		
		void Run();
		
	private:
		static App* app;
		std::vector<Layer*> layers = {};
		friend int ::main(int argc, char* argv[]);
	};
	App* CreateApp();
}


