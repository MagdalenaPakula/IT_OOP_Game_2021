#include <cmath>
#include "raycasting2DRenderer.h"
#include "scene.h"

void KUDA::Raycasting2DRenderer::DrawRays() {
    auto camera = scene.lock()->camera.get();
    if ( camera == nullptr )
        throw std::runtime_error( "Current scene has no camera" );

    auto startPosition = sf::Vector2{ camera->GetControlledPawn().GetPositionX() / 100.f * (float) window.lock()->GetWidth(),
                                      camera->GetControlledPawn().GetPositionY() / 100.f * (float) window.lock()->GetHeight() };

    for ( const auto& ray: rays ) {
        if ( ray.length >= INFINITY)
            continue;
        sf::Vertex line[] = { sf::Vertex( sf::Vector2f( ray.endX / 100.f * (float) window.lock()->GetWidth(),
                                                        ray.endY / 100.f * (float) window.lock()->GetHeight())),
                              sf::Vertex( startPosition ) };
        line[0].color = RayColor;
        line[1].color = RayColor;

        window.lock()->Draw( line, 2, sf::Lines );
    }
}

void KUDA::Raycasting2DRenderer::DrawFrame() {
    CastRays();
    Simple2DRenderer::DrawFrame();
    DrawRays();
}
