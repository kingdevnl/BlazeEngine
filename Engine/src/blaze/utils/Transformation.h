#ifndef BLAZE_TRANSFORMATION_H
#define BLAZE_TRANSFORMATION_H

#include <glm/glm.hpp>


namespace Blaze::Utils::Transformation {
    glm::mat4 getProjectionMatrix(float fov, float z_near, float z_far);
    glm::mat4 getDefaultProjectionMatrix();

    glm::mat4 getWorldMatrix(glm::vec3 pos, glm::vec3 rotation, float scale);

}


#endif //BLAZE_TRANSFORMATION_H
