#include <glm/glm.hpp>

namespace Blaze::Components
{
	struct TransformComponent;
}

namespace Blaze::Render::Math
{

	glm::mat4 GetProjectionMatrix();
	glm::mat4 GetWorldMatrix(glm::vec3 pos, glm::vec3 rot, float scale);
	glm::mat4 GetWorldMatrix(Components::TransformComponent transform);
}
