#include <entt/entt.hpp>


namespace Blaze
{
	class Entity;
	class Scene
	{
	public:
		Scene();

		void Setup();
		
		Entity CreateEntity(const std::string tag = std::string());
		void DestroyEntity(Entity entity);
		
		void OnUpdate(float dt);
		void OnRender();
		void OnDestroy();

		entt::registry registry;


	};
}
