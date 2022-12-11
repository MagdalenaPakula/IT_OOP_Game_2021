#include "renderer.h"

void KUDA::Renderer::AttachTo( std::weak_ptr <Window> newWindow ) {
    this->window = std::move(newWindow);
}
