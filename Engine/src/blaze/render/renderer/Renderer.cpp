#include "Renderer.h"
#include "../shader/Shader.h"
#include "../mesh/Mesh.h"
#include "../math/Transformation.h"
#include "../Texture.h"
#include "spdlog/spdlog.h"

namespace Blaze::Render
{
	void Renderer::Submit(Ref<Shader> shader, Ref<Mesh> mesh, glm::mat4 worldMatrix)
	{
	
		shader->Bind();
		bool hasTexture = mesh->HasTexture();

		if(hasTexture)
		{
			spdlog::info("bind texture");
			mesh->GetTexture()->Bind();
		}
		
		shader->SetInt("hasTexture", hasTexture ? 1 : 0);

		
		shader->SetMat4(std::string("projectionMatrix"), Math::GetProjectionMatrix());
		shader->SetMat4("worldMatrix", worldMatrix);
		mesh->Render();
		shader->Unbind();
	}
}
