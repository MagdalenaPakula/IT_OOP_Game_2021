#include "textureAtlas.h"

KUDA::TextureAtlas::TextureAtlas( const std::string& textureFile, int textureSize ) : textureSize( textureSize ) {
    if ( !( textures.loadFromFile( textureFile )))
        throw std::runtime_error( "Texture file could not be loaded." );
}

int KUDA::TextureAtlas::GetTextureSize() const {
    return textureSize;
}

KUDA::TextureAtlas& KUDA::TextureAtlas::WithMapping( unsigned int textureNumber, int x, int y ) {
    return this->WithMapping( textureNumber, { x, y, textureSize, textureSize } );
}

KUDA::TextureAtlas& KUDA::TextureAtlas::WithMapping( unsigned int textureNumber, KUDA::Rectangle location ) {
    mapping[textureNumber] = location;
    return *this;
}

void KUDA::TextureAtlas::SetTextureOf( sf::Sprite& sprite, unsigned int textureNumber, int offsetX, int offsetY ) {
    if ( !mapping.contains( textureNumber ))
        throw std::runtime_error( "Texture not found in _atlas!" );
    sprite.setTexture( textures );
    sprite.setTextureRect( { mapping[textureNumber].x + offsetX,
                             mapping[textureNumber].y + offsetY,
                             mapping[textureNumber].width - offsetX,
                             mapping[textureNumber].height - offsetY, } );
}
