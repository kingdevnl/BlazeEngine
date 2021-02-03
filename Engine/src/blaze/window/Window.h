#ifndef BLAZE_WINDOW_H
#define BLAZE_WINDOW_H

#include<memory>

typedef struct GLFWwindow GLFWwindow;


namespace Blaze {
    class Scene;

    class Window {
    public:
        static inline GLFWwindow *handle;
        static inline int width, height;

        static void Create(int w, int h, std::shared_ptr<Scene> initScene);

        static inline std::shared_ptr<Scene> scene;
    };

}

#endif //BLAZE_WINDOW_H
