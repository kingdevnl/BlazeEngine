#include "Scene.h"
#include "entity/Entity.h"
#include "entity/components/Components.h"
#include "spdlog/spdlog.h"
#include "../render/mesh/Mesh.h"
#include "../render/shader/Shader.h"
#include "../render/math/Transformation.h"

namespace Blaze
{
	Scene::Scene()
	{
	}

	
	void Scene::Setup()
	{
		for (auto e : registry.view<Components::MeshComponent>())
		{
			registry.get<Components::MeshComponent>(e).mesh->Create();
		}
	}

	Entity Scene::CreateEntity(const std::string tag)
	{
		Entity entity = {registry.create(), this};

		auto& tagComponent = entity.AddComponent<Components::TagComponent>(tag);

		if (tagComponent.tag.empty())
		{
			tagComponent.tag = std::string("Entity");
		}

		entity.AddComponent<Components::TransformComponent>();


		return entity;
	}

	void Scene::DestroyEntity(Entity entity)
	{
		registry.destroy(entity);
	}

	void Scene::OnUpdate(float dt)
	{
	}

	void Scene::OnRender()
	{
		for (auto e : registry.view<Components::MeshComponent, Components::TransformComponent>())
		{
			auto const meshComponent = registry.get<Components::MeshComponent>(e);
			auto& transformComponent = registry.get<Components::TransformComponent>(e);
			
			
			meshComponent.shader->SetMat4(std::string("worldMatrix"),
			                              Render::Math::GetWorldMatrix(transformComponent));
			meshComponent.mesh->Render();
		
		}
	}

	void Scene::OnDestroy()
	{
		spdlog::info("Scene::OnDestroy()");
		auto view = registry.view<Components::MeshComponent>();
		for (auto e : view)
		{
			registry.get<Components::MeshComponent>(e).mesh->Destroy();
		}
	}
}
