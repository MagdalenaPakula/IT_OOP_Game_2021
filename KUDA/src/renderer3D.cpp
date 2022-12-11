#include <cmath>
#include <iostream>
#include "renderer3D.h"
#include "scene.h"

KUDA::Renderer3D::Renderer3D( std::unique_ptr<LightingAnalyzer> ligtingAnalyzer ) : lightingAnalyzer( std::move(
        ligtingAnalyzer )) {
}

void KUDA::Renderer3D::DrawFrame() {
    if ( window.expired())
        throw std::runtime_error( "3D renderer has no window attached" );
    if ( scene.expired())
        throw std::runtime_error( "3D renderer has no scene to render" );
    float height = window.lock()->GetHeight();
    float width = window.lock()->GetWidth();
    sf::Vertex floor[] = { sf::Vertex{{ 0, height / 2 }, sf::Color::Black },
                           sf::Vertex{{ 0, height }, sf::Color( 0x80, 0x80, 0x80 ) },
                           sf::Vertex{{ width, height }, sf::Color( 0x80, 0x80, 0x80 ) },
                           sf::Vertex{{ width, height / 2 }, sf::Color::Black }, };
    sf::Vertex ceiling[] = { sf::Vertex{{ 0, height / 2 }, sf::Color::Black },
                             sf::Vertex{{ 0, 0 }, sf::Color( 0x80, 0x80, 0x80 ) },
                             sf::Vertex{{ width, 0 }, sf::Color( 0x80, 0x80, 0x80 ) },
                             sf::Vertex{{ width, height / 2 }, sf::Color::Black }, };
    window.lock()->Draw( floor, 4, sf::Quads );
    window.lock()->Draw( ceiling, 4, sf::Quads );
    CastRays();
    DrawWalls( INFINITY );
    DrawActors();
}

void KUDA::Renderer3D::DrawWalls( float maxDistance ) {
    if ( lightingAnalyzer == nullptr )
        lightingAnalyzer = std::make_unique<LightingAnalyzer>();
    auto camera = scene.lock()->camera.get();
    if ( camera == nullptr )
        throw std::runtime_error( "3D renderer has no camera" );
    int barWidth = static_cast<int>(( window.lock()->GetWidth())) / static_cast<int>(rays.size());
    int positionX = 0.f;
    const float scaleFactor = ( 0.5 * 100.f / scene.lock()->map->GetHeight()) / tan( 0.5 * camera->GetFieldOfView());
    for ( const auto& ray: rays ) {
        if ( ray.length > maxDistance ) {
            positionX += barWidth;
            continue;
        }
        positionX += barWidth;
        std::unique_ptr<sf::Drawable> rect;
        float direction;
        switch ( ray.lightDirection ) {
            case Ray::North:direction = M_PI_2;
                break;
            case Ray::East:direction = 0.f;
                break;
            case Ray::West:direction = M_PI;
                break;
            case Ray::South:direction = 3 * M_PI_2;
                break;
            default:throw std::runtime_error( "Ray direction not valid" );
        }
        int windowHeight = window.lock()->GetHeight();
        try {
            float tileOffset;
            switch ( ray.lightDirection ) {
                case Ray::North:
                case Ray::South: tileOffset = ray.endX;
                    break;
                case Ray::East:
                case Ray::West: tileOffset = ray.endY;
                    break;
            }
            auto tileSize = 100.f / static_cast<float>(scene.lock()->map->GetWidth());
            while ( tileOffset > tileSize ) tileOffset -= tileSize;
            auto textureOffset = tileOffset / tileSize;
            rect = lightingAnalyzer->Textured( { positionX,
                                                 windowHeight / 2,
                                                 barWidth,
                                                 static_cast<int>(windowHeight / ( abs( cos( camera->GetControlledPawn().GetDirection() - ray.direction )) * ray.length ) * scaleFactor) },
                                               ray.hitWall,
                                               textureOffset,
                                               direction,
                                               ray.length );
        } catch ( std::exception& error ) {
            rect = lightingAnalyzer->Colored( { positionX,
                                                windowHeight / 2,
                                                barWidth,
                                                static_cast<int>(windowHeight / ( abs( cos( camera->GetControlledPawn().GetDirection() - ray.direction )) * ray.length ) * scaleFactor) },
                                              { 180, 180, 180 },
                                              direction,
                                              ray.length );
        }
        window.lock()->Draw( *rect );
    }
}

void KUDA::Renderer3D::DrawActors() {
    const std::shared_ptr<Scene>& sceneLock = scene.lock();
    auto camera = sceneLock->camera.get();
    const float scaleFactor = ( 0.5f * 100 / scene.lock()->map->GetHeight()) / static_cast<float>(tan( 0.5 * camera->GetFieldOfView()));
    std::sort( sceneLock->actors.begin(),
               sceneLock->actors.end(),
               [&camera]( const auto l,
                          const auto r ) { return camera->DistanceTo( *l ) > camera->DistanceTo( *r ); } );
    for ( const auto& actor: sceneLock->actors ) {
        if ( actor.get() == &camera->GetControlledPawn()) continue;
        if ( abs( camera->DirectionTo( *actor )) > camera->GetFieldOfView() * 1.5 / 2 ) continue;
        auto actorSprite = actor->Get3DSprite( camera->DirectionTo( *actor ));

        float x = ( 1 + camera->DirectionTo( *actor ) / ( camera->GetFieldOfView() / 2 )) * 0.5f * static_cast<float>(window.lock()->GetWidth());
        float y = 0.5f * ( window.lock()->GetHeight() + ( window.lock()->GetHeight() / ( abs( cos( camera->DirectionTo(
                *actor ))) * camera->DistanceTo( *actor )) * scaleFactor ));
        actorSprite->setPosition( x, y );
        actorSprite->scale( 10 / ( abs( cos( camera->DirectionTo( *actor ))) * camera->DistanceTo( *actor )),
                            10 / ( abs( cos( camera->DirectionTo( *actor ))) * camera->DistanceTo( *actor )));
        lightingAnalyzer->ShadeObject( actorSprite.get(), camera->DistanceTo( *actor ));
        window.lock()->Draw( *dynamic_cast<sf::Drawable*>(actorSprite.get()));
        DrawWalls( camera->DistanceTo( *actor ));
    }
}
