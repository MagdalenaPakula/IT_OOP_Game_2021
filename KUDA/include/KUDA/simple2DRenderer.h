#ifndef GAME_SIMPLE2DRENDERER_H
#define GAME_SIMPLE2DRENDERER_H

#include "sceneRenderer.h"

namespace KUDA
{
    class Simple2DRenderer : virtual public SceneRenderer
    {
    protected:
        void DrawActors() override;

        void DrawWalls();

    public:
        void DrawFrame() override;
    };
}


#endif //GAME_SIMPLE2DRENDERER_H
