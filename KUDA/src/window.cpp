#include "window.h"
#include "IController.h"

KUDA::Window::Window( std::weak_ptr<IController>  controller,
                      int width,
                      int height,
                      unsigned int fps,
                      const std::string& title ) : _controller(std::move( controller )),
                                                   _width( width ),
                                                   _height( height ),
                                                   FPS( fps ),
                                                   _window( sf::VideoMode( width, height ),
                                                            title,
                                                            sf::Style::Titlebar | sf::Style::Close ) {}

int KUDA::Window::GetWidth() const {
    return _width;
}

int KUDA::Window::GetHeight() const {
    return _height;
}

void KUDA::Window::Loop() {
    if ( _controller.expired())
        throw std::runtime_error( "Window has no controller" );
    _controller.lock()->OnUpdate( 0 );
}

void KUDA::Window::Run() {
    while ( _window.isOpen()) {
        sf::Event event{};
        while ( _window.pollEvent( event )) {
            if ( event.type == sf::Event::Closed )
                _window.close();
        }
        Loop();
        sf::sleep( sf::milliseconds( 1000 / static_cast<int>(FPS) ));
    }
}

void KUDA::Window::FrameStart() {
    _window.clear( sf::Color::Black );
}

void KUDA::Window::FrameEnd() {
    _window.display();
}
