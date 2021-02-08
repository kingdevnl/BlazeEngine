#include "Entity.h"

namespace Blaze
{
	Entity::Entity(entt::entity handle, Scene* scene)
		: handle(handle), scene(scene)
	{
	}
}
