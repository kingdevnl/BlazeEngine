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

        mesh = std::make_shared<Blaze::Mesh>(
                std::vector<float>{
                        // VO
                        -0.5f,  0.5f,  0.5f,
                        // V1
                        -0.5f, -0.5f,  0.5f,
                        // V2
                        0.5f, -0.5f,  0.5f,
                        // V3
                        0.5f,  0.5f,  0.5f,
                        // V4
                        -0.5f,  0.5f, -0.5f,
                        // V5
                        0.5f,  0.5f, -0.5f,
                        // V6
                        -0.5f, -0.5f, -0.5f,
                        // V7
                        0.5f, -0.5f, -0.5f,
                }, std::vector<int>{
                        // Front face
                        0, 1, 3, 3, 1, 2,
                        // Top Face
                        4, 0, 3, 5, 4, 3,
                        // Right face
                        3, 2, 7, 5, 3, 7,
                        // Left face
                        6, 1, 0, 6, 0, 4,
                        // Bottom face
                        2, 1, 6, 2, 6, 7,
                        // Back face
                        7, 6, 4, 7, 4, 5,
                });
        mesh->Create();


    }

    glm::vec3 position = glm::vec3(0, 0, -5);
    glm::vec3 rotation = glm::vec3(0, 0, 0);
    float scale = 1.0f;

    void Update(float dt) override {
        Scene::Update(dt);
        rotation.x += dt * 15;
        rotation.y += dt * 15;


    }


    void Render() override {
        Scene::Render();
        shader->Bind();


        shader->UploadMat4(std::string("projectionMatrix"), Blaze::Utils::Transformation::getDefaultProjectionMatrix());
        shader->UploadMat4(std::string("worldMatrix"),
                           Blaze::Utils::Transformation::getWorldMatrix(position, rotation, scale));

        glEnable(GL_DEPTH_TEST);
        mesh->Render();
        glDisable(GL_DEPTH_TEST);

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