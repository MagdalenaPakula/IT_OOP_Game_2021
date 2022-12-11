#include "sceneRenderer.h"

void KUDA::SceneRenderer::SetScene( std::weak_ptr<Scene> newScene ) {
    scene = std::move( newScene );
}
