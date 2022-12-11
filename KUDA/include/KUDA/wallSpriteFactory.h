#ifndef GAME_WALLSPRITEFACTORY_H
#define GAME_WALLSPRITEFACTORY_H

#include <memory>
#include <SFML/graphics.hpp>
#include "rectangle.h"

namespace KUDA
{
    class TextureAtlas;

    class WallSpriteFactory
    {
    private:
        std::weak_ptr<TextureAtlas> _atlas;
    public:
        explicit WallSpriteFactory( std::weak_ptr<TextureAtlas>  atlas );
        WallSpriteFactory() = default;

    public:

        void SetTextureAtlas( std::weak_ptr<TextureAtlas> atlas );

        std::unique_ptr<sf::Drawable> Colored( Rectangle bounds, sf::Color color );

        std::unique_ptr<sf::Sprite> Textured( Rectangle bounds, int textureNumber, float textureOffset );
    };
}


#endif //GAME_WALLSPRITEFACTORY_H
