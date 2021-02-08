#include "../layer/Layer.h"
#include "../../app/App.h"
#include "spdlog/spdlog.h"

namespace Blaze
{
	void Layer::Setup()
	{
	}

	

	void Layer::OnUpdate(float dt)
	{
		std::shared_ptr<Scene> scene = App::GetApp()->currentScene;

		scene->OnUpdate(dt);
	}

	void Layer::OnRender()
	{
		std::shared_ptr<Scene> scene = App::GetApp()->currentScene;

		scene->OnRender();
	}

	void Layer::OnImGui()
	{
	}

	void Layer::OnDestroy()
	{
		spdlog::info("layer::Destroy()");
	}
}
