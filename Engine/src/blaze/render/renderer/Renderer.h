#pragma once
#include "../../Blaze.h"
#include "glm/fwd.hpp"

namespace Blaze::Render
{
	class Shader;
	class Mesh;

	class Renderer
	{
	public:
		static void Submit(Ref<Shader> shader, Ref<Mesh> mesh, glm::mat4 worldMatrix);
	};
}
