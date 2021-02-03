#include "Transformation.h"
#include "Math.h"
#include "../window/Window.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Blaze::Utils::Transformation {

    glm::mat4 getProjectionMatrix(float fov, float z_near, float z_far) {

        float width = Blaze::Window::width;
        float height = Blaze::Window::height;
        width = Min(width, 10);
        height = Min(height, 10);

        float aspect = (float) width / height;
        return glm::perspective(fov, aspect, z_near, z_far);
    }

    glm::mat4 Transformation::getDefaultProjectionMatrix() {
        return getProjectionMatrix(ToRadians(60), 0.01f, 1000.f);
    }

    glm::mat4 getWorldMatrix(glm::vec3 pos, glm::vec3 rotation, float scale) {
        glm::mat4 worldMatrix = glm::mat4(1.0);
        worldMatrix = glm::translate(worldMatrix, pos);
        worldMatrix = glm::rotate<float>(worldMatrix, glm::radians(rotation.x), glm::vec3(1, 0, 0));
        worldMatrix = glm::rotate<float>(worldMatrix, glm::radians(rotation.y), glm::vec3(0, 1, 0));
        worldMatrix = glm::rotate<float>(worldMatrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));
        worldMatrix = glm::scale(worldMatrix, glm::vec3(scale, scale, scale));
        return worldMatrix;
    }

}
