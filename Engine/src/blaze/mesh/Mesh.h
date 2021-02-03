//
// Created by jasper on 3-2-2021.
//

#ifndef BLAZE_MESH_H
#define BLAZE_MESH_H

#include <vector>

namespace Blaze {
    class Mesh {
    private:
        std::vector<unsigned int> vbos = {};
        std::vector<float> positions;
        int vertexCount = 0;
        unsigned int vao = -1;

    public:
        Mesh(const std::vector<float> &positions);

        void Create();
        void Render();
        void Destroy();


    };

}


#endif //BLAZE_MESH_H
