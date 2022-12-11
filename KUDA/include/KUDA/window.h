#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <memory>
#include <SFML/graphics.hpp>

namespace KUDA
{
    class IController;

    class Window
    {
        friend class Renderer;

    private:
        sf::RenderWindow _window;
        std::weak_ptr<IController> _controller;
        int _width;
        int _height;

    public:
        unsigned int FPS = 60;

    public:
        Window( std::weak_ptr<IController>  controller,
                int width,
                int height,
                unsigned int fps,
                const std::string& title );

        int GetWidth() const;

        int GetHeight() const;

        void Loop();

        void Run();

        void FrameStart();

        void FrameEnd();

        template<typename... Args>
        void Draw( Args&& ... args ) {
            _window.draw( std::forward<Args>( args )... );
        }
    };
}


#endif //GAME_WINDOW_H
