#ifndef GAME_RENDERER_H
#define GAME_RENDERER_H

#include <memory>
#include "window.h"

namespace KUDA
{
    class Renderer
    {
    protected:
        std::weak_ptr<Window> window;
    public:
        virtual ~Renderer() = default;
    public:
        void AttachTo( std::weak_ptr<Window> newWindow );

        virtual void DrawFrame() = 0;
    };
}


#endif //GAME_RENDERER_H
