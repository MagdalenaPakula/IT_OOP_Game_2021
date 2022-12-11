#ifndef GAME_TEXTUREATLAS_H
#define GAME_TEXTUREATLAS_H

#include <map>
#include <SFML/graphics.hpp>
#include "rectangle.h"

namespace KUDA
{
    class TextureAtlas
    {
    private:
        sf::Texture textures;
        const int textureSize;
        std::map<unsigned int, Rectangle> mapping;
    public:
        TextureAtlas( const std::string& textureFile, int textureSize );

        int GetTextureSize() const;

        TextureAtlas& WithMapping( unsigned int textureNumber, int x, int y );

        TextureAtlas& WithMapping( unsigned int textureNumber, Rectangle location );

        void SetTextureOf( sf::Sprite& sprite, unsigned int textureNumber, int offsetX = 0, int offsetY = 0 );
    };
}


#endif //GAME_TEXTUREATLAS_H
