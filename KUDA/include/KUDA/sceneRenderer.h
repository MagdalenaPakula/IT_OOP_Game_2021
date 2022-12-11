#ifndef GAME_SCENERENDERER_H
#define GAME_SCENERENDERER_H

#include <memory>
#include "renderer.h"

namespace KUDA
{
    class Scene;

    class SceneRenderer : public Renderer
    {
    protected:
        std::weak_ptr<Scene> scene;

    protected:
        virtual void DrawActors() = 0;

    public:
        virtual void SetScene( std::weak_ptr<Scene> newScene );
    };
}


#endif //GAME_SCENERENDERER_H
