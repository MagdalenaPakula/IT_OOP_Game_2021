#include "wallSpriteFactory.h"
#include "textureAtlas.h"

#include <memory>

KUDA::WallSpriteFactory::WallSpriteFactory( std::weak_ptr<TextureAtlas>  atlas ) : _atlas(std::move( atlas )) {
}

void KUDA::WallSpriteFactory::SetTextureAtlas( std::weak_ptr<TextureAtlas> atlas ) {
    _atlas = std::move( atlas );
}

std::unique_ptr<sf::Drawable> KUDA::WallSpriteFactory::Colored( KUDA::Rectangle bounds, sf::Color color ) {
    auto rect = std::make_unique<sf::RectangleShape>( sf::Vector2f{ static_cast<float>(bounds.width),
                                                                    static_cast<float>(bounds.height) } );
    rect->setOrigin(( static_cast<float>(( bounds.width )) / 2 ), ( static_cast<float>(( bounds.height )) / 2 ));
    rect->setPosition( static_cast<float>(bounds.x), static_cast<float>(bounds.y));
    rect->setFillColor( color );
    return rect;
}

std::unique_ptr<sf::Sprite> KUDA::WallSpriteFactory::Textured( KUDA::Rectangle bounds,
                                                               int textureNumber,
                                                               float textureOffset ) {
    auto atlas = _atlas.lock();
    if ( atlas == nullptr )
        throw std::runtime_error( "Texture atlas unavailable" );
    auto rect = std::make_unique<sf::Sprite>();
    auto offset = static_cast<int>((textureOffset * static_cast<float>(atlas->GetTextureSize())));
    atlas->SetTextureOf( *rect, textureNumber, offset );
    auto textureRect = rect->getTextureRect();
    textureRect.width = 1;
    rect->setTextureRect( textureRect );
    rect->setOrigin( static_cast<float>(( bounds.width )) / 2, static_cast<float>(( atlas->GetTextureSize())) / 2 );
    rect->setScale( 1, ( static_cast<float>(bounds.height) / static_cast<float>(atlas->GetTextureSize())));
    rect->setPosition( static_cast<float>(bounds.x), static_cast<float>(bounds.y));
    return rect;
}
