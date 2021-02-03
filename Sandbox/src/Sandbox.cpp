#include <blaze/window/Window.h>
#include "blaze/Blaze.h"
#include <blaze/scene/Scene.h>
#include <spdlog/spdlog.h>
#include <GL/glew.h>
#include <blaze/shader/Shader.h>
#include <fstream>
#include <blaze/utils/Transformation.h>
#include <blaze/mesh/Mesh.h>

class MyScene : public Blaze::Scene {

    std::shared_ptr<Blaze::Shader> shader;
    std::shared_ptr<Blaze::Mesh> mesh;

    void Init() override {
        Scene::Init();
        spdlog::info("MyScene::Init()");
        shader = std::make_shared<Blaze::Shader>();

        std::ifstream vertexStream("res/vertex.glsl");
        std::ifstream fragmentStream("res/fragment.glsl");
        if (!vertexStream.is_open() | !fragmentStream.is_open()) {
            spdlog::error("Failed to open shader files!");
            throw "Shader error!";
        }

        shader->Create(
                std::string((std::istreambuf_iterator<char>(vertexStream)),
                            std::istreambuf_iterator<char>()).c_str(),
                std::string((std::istreambuf_iterator<char>(fragmentStream)),
                            std::istreambuf_iterator<char>()).c_str()
        );
        vertexStream.close();
        fragmentStream.close();

        mesh = std::make_shared<Blaze::Mesh>(std::vector<float>{
                -1, -1, -2.5f,
                1, -1, -2.5f,
                0, 1, -2.5f,
        });
        mesh->Create();




    }

    void Update(float dt) override {
        Scene::Update(dt);

        glRotatef(dt * 5, 0, 0, 1);

    }

    void Render() override {
        Scene::Render();
        shader->Bind();


        shader->UploadMat4(std::string("projectionMatrix"),  Blaze::Utils::Transformation::getDefaultProjectionMatrix());

        mesh->Render();


        shader->Unbind();
    }

    void Destroy() override {
        Scene::Destroy();
        shader->Destroy();
        mesh->Destroy();
    }
};

int main() {


    Blaze::Setup();


    Blaze::Window::Create(1080, 720, std::make_shared<MyScene>());


    return 0;
}