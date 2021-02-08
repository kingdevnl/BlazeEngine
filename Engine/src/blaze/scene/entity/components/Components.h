#pragma once
#include <string>
#include <utility>


#include "../../../Blaze.h"
#include "glm/vec3.hpp"
#include "spdlog/spdlog.h"

namespace Blaze
{
	namespace Render
	{
		class Shader;
		class Mesh;
	}

	namespace Components
	{
		struct TagComponent
		{
			std::string tag;

			explicit TagComponent(::std::string tag)
				: tag(std::move(tag))
			{
			}
		};

		struct TransformComponent
		{
			glm::vec3 position{0, 0, 0};
			glm::vec3 rotation{0, 0, 0};
			float scale = 1.0;

			TransformComponent()
			{
				spdlog::info("TransformComponent()");
			};


			TransformComponent(const ::glm::vec3& position, const ::glm::vec3& rotation, float scale)
				: position(position),
				  rotation(rotation),
				  scale(scale)
			{
				spdlog::info("TransformComponent({} {} {})", 1, 1, 1);
			}
		};

		struct MeshComponent
		{
			Ref<Render::Mesh> mesh;
			
			Ref<Render::Shader> shader;


			MeshComponent(const Ref<Render::Mesh>& mesh, const Ref<Render::Shader>& shader)
				: mesh(mesh),
				  shader(shader)
			{
			}
		};
	}
}
