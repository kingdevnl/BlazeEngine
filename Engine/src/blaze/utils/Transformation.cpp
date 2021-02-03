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

        float aspect = (float) width/ height;
        return glm::perspective(fov, aspect, z_near, z_far);
    }

     glm::mat4 Transformation::getDefaultProjectionMatrix() {
        return getProjectionMatrix(ToRadians(60), 0.01f, 1000.f);
    }

}
