//
// Created by jasper on 3-2-2021.
//

#include "Mesh.h"
#include <gl/glew.h>

namespace Blaze {
    Mesh::Mesh(const std::vector<float> &positions) : positions(positions) {}

    void Mesh::Create() {
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);


        auto makeVBO = [this]() {
            unsigned int vbo;
            glGenBuffers(1, &vbo);
            vbos.push_back(vbo);
            return vbo;
        };

        unsigned int vbo = makeVBO();

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(float), &positions[0], GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        vertexCount = positions.size() / 3;

    }

    void Mesh::Destroy() {
        for (unsigned int vbo : vbos) {
            glDeleteBuffers(1, &vbo);
        }
        glDeleteVertexArrays(1, &vao);
    }

    void Mesh::Render() {
        glBindVertexArray(vao);
        glEnableVertexAttribArray(0);
        glDrawArrays(GL_TRIANGLES, 0, vertexCount);
        glDisableVertexAttribArray(0);
        glBindVertexArray(0);
    }

}
