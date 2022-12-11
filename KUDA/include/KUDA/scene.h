#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include <memory>
#include <vector>
#include "IMap.h"
#include "actor.h"
#include "camera.h"

namespace KUDA
{
    class Scene
    {
    public:
        std::unique_ptr<IMap> map;
        std::vector<std::shared_ptr<Actor>> actors;
        std::unique_ptr<Camera> camera;
    };
}


#endif //GAME_SCENE_H
