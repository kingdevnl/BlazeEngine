#ifndef BLAZE_SHADER_H
#define BLAZE_SHADER_H
#include <string>
#include <map>
#include <glm/mat4x4.hpp>

namespace Blaze {
    class Shader {
    private:
        int programID = -1, vertexID = -1, fragmentID = -1;
        std::string name;
        std::map<std::string, int> uniformLocations = {};
    public:

        void Create(const char* vertexSource, const char* fragmentSource);

        void Bind();

        void UploadMat4(std::string name, glm::mat4 value);


        void Unbind();
        void Destroy();
    };

}


#endif //BLAZE_SHADER_H
