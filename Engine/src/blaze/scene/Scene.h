#ifndef BLAZE_SCENE_H
#define BLAZE_SCENE_H

namespace Blaze {

    class Scene {
    public:
        virtual void Init();
        virtual void Update(float dt);
        virtual void Render();
        virtual void Destroy();
    };

}


#endif //BLAZE_SCENE_H
