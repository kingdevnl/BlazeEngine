#include "Transformation.h"
#include "../../app/App.h"
#include "../../scene/entity/components/Components.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

namespace Blaze::Render::Math
{
	glm::mat4 GetProjectionMatrix()
	{
		const auto window = App::GetApp()->window;
		const float aspect = static_cast<float>(static_cast<float>(window->width) / static_cast<float>(window->height));

		return glm::perspective(static_cast<float>(glm::radians(60.0f)), aspect, 0.01f, 1000.f);
	}

	glm::mat4 GetWorldMatrix(glm::vec3 pos, glm::vec3 rot, float scale)
	{
		glm::mat4 worldMatrix = glm::mat4(1.0);
		worldMatrix = glm::translate(worldMatrix, pos);
		worldMatrix = glm::rotate<float>(worldMatrix, glm::radians(rot.x), glm::vec3(1, 0, 0));
		worldMatrix = glm::rotate<float>(worldMatrix, glm::radians(rot.y), glm::vec3(0, 1, 0));
		worldMatrix = glm::rotate<float>(worldMatrix, glm::radians(rot.z), glm::vec3(0, 0, 1));
		worldMatrix = glm::scale(worldMatrix, glm::vec3(scale, scale, scale));
		return worldMatrix;
	}

	glm::mat4 GetWorldMatrix(Components::TransformComponent transform)
	{
		return GetWorldMatrix(transform.position, transform.rotation, transform.scale);
	}
}
