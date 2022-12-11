#include <cmath>
#include "simple2DRenderer.h"
#include "scene.h"

#define SFML_TRANSFORM_ANGLE( x ) ((x) / M_PI * -180)

void KUDA::Simple2DRenderer::DrawActors() {
    auto win = window.lock();
    for ( const auto actor: scene.lock()->actors ) {
        auto c = actor->Get2DSprite();
        c->setPosition( actor->GetPositionX() / 100.f * static_cast<float>(window.lock()->GetWidth()),
                        actor->GetPositionY() / 100.f * static_cast<float>(window.lock()->GetHeight()));
        c->setRotation(SFML_TRANSFORM_ANGLE( actor->GetDirection()));
        win->Draw( *dynamic_cast<sf::Drawable*>(c.get()));
    }
}

void KUDA::Simple2DRenderer::DrawWalls() {
    const IMap* const map = scene.lock()->map.get();
    const auto mapWidth = static_cast<float>(map->GetWidth());
    const auto mapHeight = static_cast<float>(map->GetHeight());
    const auto tileWidth = static_cast<float>(window.lock()->GetWidth()) / mapWidth;
    const auto tileHeight = static_cast<float>(window.lock()->GetHeight()) / mapHeight;
    for ( int row = 0; row < map->GetHeight(); ++row ) {
        for ( int col = 0; col < map->GetWidth(); ++col ) {
            if ( map->IsWall(( static_cast<float>(col) + .5f ) * 100.f / mapWidth, ( static_cast<float>(row) + .5f ) * 100.f / mapHeight )) {
                sf::RectangleShape tile( sf::Vector2f( tileWidth, tileHeight ));
                tile.setFillColor( sf::Color::White );
                tile.setPosition((float) col * tileWidth, (float) row * tileHeight );
                window.lock()->Draw( tile );
            }
        }
    }
}

void KUDA::Simple2DRenderer::DrawFrame() {
    if ( window.expired())
        throw std::runtime_error( "Renderer has no window to draw to." );
    if ( scene.expired())
        throw std::runtime_error( "Renderer has no scene to render" );
    DrawWalls();
    DrawActors();
}
