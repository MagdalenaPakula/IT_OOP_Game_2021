#ifndef GAME_RAYCASTINGRENDERER_H
#define GAME_RAYCASTINGRENDERER_H

#include "sceneRenderer.h"
#include "ray.h"

namespace KUDA
{
    class RaycastingRenderer : virtual public SceneRenderer
    {
    protected:
        std::vector<Ray> rays;
    public:

        void CastRays();
    };
}


#endif //GAME_RAYCASTINGRENDERER_H
