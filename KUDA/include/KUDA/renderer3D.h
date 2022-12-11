#ifndef GAME_RENDERER3D_H
#define GAME_RENDERER3D_H

#include "raycastingRenderer.h"
#include "lightingAnalyzer.h"

namespace KUDA
{
    class Renderer3D : public RaycastingRenderer
    {
    public:
        std::unique_ptr<LightingAnalyzer> lightingAnalyzer;
    public:
        explicit Renderer3D( std::unique_ptr<LightingAnalyzer> ligtingAnalyzer );

        void DrawFrame() override;

    private:
        void DrawWalls( float maxDistance );

        void DrawActors() override;
    };
}


#endif //GAME_RENDERER3D_H
