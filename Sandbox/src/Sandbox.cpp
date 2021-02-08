#include <gl/glew.h>

#include <blaze/app/App.h>
#include <blaze/render/mesh/Mesh.h>
#include <blaze/render/layer/Layer.h>
#include <blaze/scene/entity/Entity.h>
#include <blaze/render/shader/Shader.h>
#include <blaze/render/math/Transformation.h>
#include <blaze/scene/entity/components/Components.h>
#include <blaze/render/Texture.h>
#include <spdlog/spdlog.h>

#include "blaze/Blaze.h"

using namespace Blaze;
using namespace Render;

class MyLayer : public Blaze::Layer
{
public:
	const float z = 0;
	// Mesh* mesh = new Mesh(
	// 	std::vector<float>{
	//
	// 		-1, 1, 0, //t-left
	// 		-1, -1, 0, //b-left
	// 		1, -1, 0, //b-right
	//
	// 		1, -1, 0, //b-right
	// 		1, 1, 0, //t-right
	// 		-1, 1, 0, //t-left
	//
	// 	},
	// 	std::vector<float>{
	// 			0, 1,
	// 			0, 0,
	// 			1, 0,
	// 		
	// 			1, 0,
	// 			1, 1,
	// 			0, 1
	// 	
	// 		
	// 		
	// 	},
	// 	std::vector<int>{0, 1, 2, 3, 4, 5}
	// );

	Ref<Texture> texture = CreateRef<Texture>("res/brick.png");
	Ref<Mesh> mesh = Mesh::LoadModel(std::string("res/plane.obj"));

	Ref<Shader> shader = CreateRef<Shader>(
		std::string(
			R"(
			#version 330 core
			layout (location=0) in vec3 pos;
			layout (location=1) in vec2 textCoord;
			out vec3 fPos;
			out vec2 fTextCoord;

			uniform mat4 projectionMatrix;
			uniform mat4 worldMatrix;
			void main() {
				fPos = pos;
				fTextCoord = textCoord;
				gl_Position = projectionMatrix * worldMatrix * vec4(pos, 1.0);
			}
		)"),
		std::string(
			R"(
			#version 330 core
			in vec3 fPos;
			in vec2 fTextCoord;
			out vec4 color;
			uniform vec3 iColor;
			uniform sampler2D texture_sampler;

			void main() {
				color = texture(texture_sampler, fTextCoord);
				//color = vec4(iColor.x+fPos.x+0.5, 0.5, iColor.y+fPos.y+0.5, 1);
			}
		)")
	);

	

	Ref<Scene> scene = App::GetApp()->currentScene;

	void Setup() override
	{
		spdlog::info("Sandbox::MyLayer::Setup()");
		std::shared_ptr<Scene> scene = App::GetApp()->currentScene;

		{
			auto entity = scene->CreateEntity();
			entity.AddComponent<Components::MeshComponent>(mesh, shader);

			auto& transform = entity.GetComponent<Components::TransformComponent>();
			transform.position.z = -5;
			transform.position.x = -2;

			transform.rotation.x = static_cast<float>(rand());
			transform.rotation.y = static_cast<float>(rand());
			transform.rotation.z = static_cast<float>(rand());

		}
		{
			auto entity = scene->CreateEntity();
			entity.AddComponent<Components::MeshComponent>(mesh, shader);

			
			auto& transform = entity.GetComponent<Components::TransformComponent>();
			transform.position.z = -5;
			transform.position.x = 2;

			transform.rotation.x = static_cast<float>(rand());
			transform.rotation.y = static_cast<float>(rand());
			transform.rotation.z = static_cast<float>(rand());

		}
		
		
		

		shader->Create();
		texture->Create();

		shader->SetInt("texture_sampler", 0);

		
		
	}

	void OnRender() override
	{
		glEnable(GL_DEPTH_TEST);
		shader->Bind();
		shader->SetMat4(std::string("projectionMatrix"), Math::GetProjectionMatrix());

		texture->Bind();
		Layer::OnRender();
		shader->Unbind();
		glDisable(GL_DEPTH_TEST);
	}

	void OnUpdate(float dt)
	{
		
		
		

		auto view = scene->registry.view<Components::TransformComponent>();

		for (auto e : view)
		{
			auto& rot = scene->registry.get<Components::TransformComponent>(e).rotation;
			rot.x -= dt * 25;
			rot.y -= dt * 25;
			rot.z -= dt * 25;
		}


		Layer::OnUpdate(dt);
	}

	void OnDestroy() override
	{
		Layer::OnDestroy();
		shader->Destroy();
		texture->Destroy();
	}
};


class MyApp : public App
{
public:
	explicit MyApp()
		: App(std::string("Sandbox"))
	{
	}

	void Setup() override
	{
		spdlog::info("Sandbox::MyApp::Setup()");
		PushLayer(new MyLayer());
		App::Setup();
	}
};

App* Blaze::CreateApp()
{
	return new MyApp();
}
