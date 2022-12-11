#include "raycastingRenderer.h"
#include "scene.h"

void KUDA::RaycastingRenderer::CastRays() {
    rays.clear();

    auto current_scene = scene.lock();
    if ( current_scene == nullptr )
        throw std::runtime_error( "Renderer has no scene to render" );

    auto camera = current_scene->camera.get();
    if ( camera == nullptr )
        throw std::runtime_error( "Current scene has no map" );

    const float positionX = camera->GetControlledPawn().GetPositionX();
    const float positionY = camera->GetControlledPawn().GetPositionY();
    const float direction = camera->GetControlledPawn().GetDirection();
    const int windowWidth = window.lock()->GetWidth();

    rays.emplace_back( *( current_scene->map ), positionX, positionY, direction );
    for ( int i = 1; i < windowWidth / 2; ++i ) {
        float angleOffset = ( camera->GetFieldOfView() / (float) windowWidth * i );
        rays.emplace_back( *( scene.lock()->map ), positionX, positionY, direction - angleOffset );
        rays.emplace( rays.begin(), *( current_scene->map ), positionX, positionY, direction + angleOffset );
    }
}
