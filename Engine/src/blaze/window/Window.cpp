#include "Window.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <utility>
#include "../scene/Scene.h"

float getTime() {
    return (float) glfwGetTime();
}

void Blaze::Window::Create(int w, int h, std::shared_ptr<Scene> initScene) {

    scene = std::move(initScene);
    width = w;
    height = h;

    glfwInit();
    glfwDefaultWindowHints();

    handle = glfwCreateWindow(width, height, "Blaze", 0, 0);

    glfwMakeContextCurrent(handle);

    glewInit();


    glfwSetWindowSizeCallback(handle, [](GLFWwindow *h, int w2, int h2) {
        width = w2;
        height = h2;
    });


    float beginTime = getTime();
    float endTime;
    float dt = -1.0f;

    scene->Init();

    while (!glfwWindowShouldClose(handle)) {
        glfwPollEvents();
        glViewport(0, 0, width, height);

        glClear(GL_COLOR_BUFFER_BIT);


        if (scene != nullptr && dt >= 0) {
            scene->Update(dt);
            scene->Render();
        }
        glfwSwapBuffers(handle);

        endTime = getTime();
        dt = endTime - beginTime;
        beginTime = endTime;

    }
    if(scene != nullptr) {
        scene->Destroy();
    }
    glfwDestroyWindow(handle);
    glfwTerminate();

}
