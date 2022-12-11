#include "KUDA.h"
#include <cmath>
#include <iostream>
#include "map.h"
#include "projectileController.h"
#include "playerController.h"

using namespace KUDA;

std::chrono::steady_clock::time_point _lastFrame;
float _deltaTime = 0;

//#define MENU_TEST
#define MAP_RENDERER_TEST

#ifdef MAP_RENDERER_TEST
#ifdef MAP
class Map : public IMap
{
    int array[10][10] = {{ 1, 2, 1, 1, 1, 1, 1, 1, 1, 1 },
                         { 1, 0, 1, 0, 0, 0, 1, 1, 1, 1 },
                         { 1, 0, 1, 0, 0, 0, 0, 0, 0, 1 },
                         { 1, 0, 1, 0, 0, 1, 0, 1, 0, 1 },
                         { 1, 0, 0, 0, 0, 0, 0, 1, 0, 1 },
                         { 1, 0, 1, 1, 1, 1, 0, 1, 0, 1 },
                         { 1, 0, 0, 0, 0, 0, 0, 1, 0, 1 },
                         { 1, 1, 1, 0, 1, 1, 1, 1, 0, 1 },
                         { 1, 0, 0, 0, 1, 1, 1, 1, 0, 1 },
                         { 1, 1, 1, 1, 1, 1, 1, 1, 3, 1 }};
public:
    int GetWidth() const override {
        return 10;
    }

    int GetHeight() const override {
        return 10;
    }

    int ValueAtPosition( float x, float y ) const override {
        return array[(int) ( y / 100.f * GetHeight())][(int) ( x / 100.f * GetWidth())];
    }

    bool IsWall( float x, float y ) const override {
        return ValueAtPosition( x, y ) == 1;
    }
};
#endif


class GameController : public IController
{
public:
    std::vector<std::shared_ptr<Renderer>> renderers = {};
    std::vector<IController*> controllers = {};
    std::vector<std::shared_ptr<Window>> windows = {};

    void OnUpdate(int timeStep) override {
        auto now = std::chrono::steady_clock::now();
        _deltaTime = (float) ( std::__1::chrono::duration_cast<std::chrono::milliseconds>( now - _lastFrame ).count());
        _lastFrame = now;
        for ( auto controller: controllers ) {
            controller->OnUpdate((int)(_deltaTime));
        }
        for ( const auto& window: windows ) {
            window->FrameStart();
        }
        for ( auto& renderer: renderers ) {
            renderer->DrawFrame();
        }
        for ( const auto& window: windows ) {
            window->FrameEnd();
        }
    }
};

class TestActor : public Actor {
public:
    TestActor( float positionX, float positionY, float direction ) : Actor( positionX, positionY, direction ) {}

    std::unique_ptr<sf::Transformable> Get2DSprite() const override {
        auto shape = std::make_unique<sf::CircleShape>(2.f);
        shape->setFillColor(sf::Color::Green);
        return std::move(shape);
    }

    std::unique_ptr<sf::Transformable> Get3DSprite( float lookingDirection ) const override {
        auto shape =  std::make_unique<sf::CircleShape>( 100.f);
        shape->setOrigin( 50, 100);
        return shape ;
    }
};

int main() {
    auto controller = std::make_shared<GameController>();
    auto controller2 = std::make_shared<GameController>();
    auto w = std::make_shared<Window>( controller, 1000, 1000, 60, "Helo" );
    auto w2 = std::make_shared<Window>( controller2, 500, 500, 60, "Helo2D" );
//    auto textureAtlas = std::make_shared<TextureAtlas>("../TestGame/textures/brickWall100.png",100);
//    textureAtlas->WithMapping(1,0,0);
    auto spriteFactory = std::make_shared<WallSpriteFactory>();
    auto analyzer = std::make_unique<LightingAnalyzer>(spriteFactory);
    analyzer->baseLightLevel = 230;
    auto renderer = std::make_shared<Renderer3D>( std::move( analyzer ));
    auto renderer2 = std::make_shared<Raycasting2DRenderer>();
    renderer->AttachTo( w );
    auto scene = std::make_shared<Scene>();
    renderer->SetScene( scene );
    renderer2->SetScene( scene );
    scene->map = std::unique_ptr<Map>(new Map {{ 1, 2, 1, 1, 1, 1, 1, 1, 1, 1 },
                                                { 1, 0, 1, 0, 0, 0, 1, 1, 1, 1 },
                                                { 1, 0, 1, 0, 0, 0, 0, 0, 0, 1 },
                                                { 1, 0, 1, 0, 0, 1, 0, 1, 0, 1 },
                                                { 1, 0, 0, 0, 0, 0, 0, 1, 0, 1 },
                                                { 1, 0, 1, 1, 1, 1, 0, 1, 0, 1 },
                                                { 1, 0, 0, 0, 0, 0, 0, 1, 0, 1 },
                                                { 1, 1, 1, 0, 1, 1, 1, 1, 0, 1 },
                                                { 1, 0, 0, 0, 1, 1, 1, 1, 0, 1 },
                                                { 1, 1, 1, 1, 1, 1, 1, 1, 3, 1 }});
    renderer2->AttachTo( w2 );
    auto playerController = std::make_unique<PlayerController>(scene);
    playerController->movementSpeed = 5;
    playerController->rotationSpeed = 1;
    auto player = std::make_shared<Player>(15,15,0,std::move(playerController),100);
    controller->controllers.push_back( &player->GetController());
    scene->actors.push_back( player );
    scene->actors.push_back(std::make_shared<TestActor>(40,40,0));
    scene->actors.push_back(std::make_shared<TestActor>(85,88,0));
    scene->camera = std::unique_ptr<Camera>( Camera::FromDegrees( player, 70 ));
    controller2->renderers.push_back( dynamic_pointer_cast<Simple2DRenderer>( renderer2 ));
    controller->renderers.push_back( renderer );
    controller->windows.push_back( w );
    controller2->windows.push_back( w2 );
    controller->controllers.push_back( controller2.get());
    _lastFrame = std::chrono::steady_clock::now();
    w->Run();
}

#endif

#ifdef MENU_TEST
class MenuController : public IController
{
private:
    bool keyPressed = false;
public:
    std::vector<std::shared_ptr<Renderer>> renderers = {};
    std::vector<IController*> controllers = {};
    std::vector<std::shared_ptr<Window>> windows = {};

    void OnUpdate(int deltaTime) override {
        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::W )) {
            if ( !keyPressed ) {
                MenuRenderer& renderer = *dynamic_cast<MenuRenderer*>(renderers[0].get());
                if ( renderer.selectedItem > 0 )
                    renderer.selectedItem--;
            }
            keyPressed = true;
        } else if ( sf::Keyboard::isKeyPressed( sf::Keyboard::S )) {
            if ( !keyPressed ) {
                MenuRenderer& renderer = *dynamic_cast<MenuRenderer*>(renderers[0].get());
                if ( renderer.selectedItem < renderer.menuItems.size() - 1 )
                    renderer.selectedItem++;
            }
            keyPressed = true;
        } else keyPressed = false;

        for ( const auto& window: windows ) {
            window->FrameStart();
        }
        for ( auto& renderer: renderers ) {
            renderer->DrawFrame();
        }
        for ( const auto& window: windows ) {
            window->FrameEnd();
        }
    }
};

int main() {
    auto menuController = std::make_shared<MenuController>();
    auto menuWindow = std::make_shared<Window>( menuController, 1000, 1000, 60, "MenuTest" );
    auto menuRenderer = std::make_shared<MenuRenderer>( "/System/Library/Fonts/Supplemental/Arial.ttf", 50 );
    menuRenderer->AttachTo( menuWindow );
    menuRenderer->SetBackground( sf::Color::Blue, 1.f );
    menuRenderer->TitleFromSting( "Menu Title", 100 );
    menuRenderer->menuItems = { "New Game", "Load", "Options", "Exit"};
    menuController->renderers.push_back( menuRenderer );
    menuController->windows.push_back( menuWindow );
    menuWindow->Run();
}
#endif