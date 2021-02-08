#pragma once
#include <entt/entt.hpp>


namespace Blaze
{
	class Scene;
	class Entity
	{
	private:
		entt::entity handle{entt::null};
		Scene* scene;
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);


		template <typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			T& component = scene->registry.emplace<T>(handle, std::forward<Args>(args)...);
			return component;
		}

		template <typename T>
		T& GetComponent()
		{
			return scene->registry.get<T>(handle);
		}

		template <typename T>
		bool HasComponent()
		{
			return scene->registry.has<T>(handle);
		}

		template <typename T>
		bool RemoveComponent()
		{
			return scene->registry.remove_if_exists<T>(handle);
		}

		operator entt::entity() const
		{
			return handle;
		}
	};
}
