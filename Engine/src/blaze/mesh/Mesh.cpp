//
// Created by jasper on 3-2-2021.
//

#include "Mesh.h"
#include <gl/glew.h>

#include <utility>

namespace Blaze {
    Mesh::Mesh(std::vector<float> positions, std::vector<int> indices) : positions(std::move(positions)), indices(std::move(indices)) {}

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



        vbo = makeVBO();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);

        vertexCount = indices.size();

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
        glEnableVertexAttribArray(1);

        glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, NULL);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glBindVertexArray(0);
    }

}
