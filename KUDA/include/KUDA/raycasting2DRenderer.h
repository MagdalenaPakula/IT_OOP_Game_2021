#ifndef GAME_RAYCASTING2DRENDERER_H
#define GAME_RAYCASTING2DRENDERER_H

#include "raycastingRenderer.h"
#include "simple2DRenderer.h"

namespace KUDA
{
    class Raycasting2DRenderer : public RaycastingRenderer, public Simple2DRenderer
    {
    private:
        const sf::Color RayColor = sf::Color::Red;
    private:
        void DrawRays();

    public:

        void DrawFrame() override;
    };
}


#endif //GAME_RAYCASTING2DRENDERER_H
