#ifndef GAME_LIGHTINGANALYZER_H
#define GAME_LIGHTINGANALYZER_H

#include <memory>
#include <SFML/graphics.hpp>
#include "rectangle.h"

namespace KUDA
{
    class WallSpriteFactory;

    class LightingAnalyzer
    {
    public:
        uint8_t baseLightLevel = 0;
        float lightingDirection = 0;
        float shadingIntensity = 10;
        float fogIntensity = 30;
        float fogExponent = 2;
        std::shared_ptr<WallSpriteFactory> spriteFactory = nullptr;
    public:
        LightingAnalyzer() = default;

        explicit LightingAnalyzer( std::shared_ptr<WallSpriteFactory> spriteFactory );

        [[nodiscard]] std::unique_ptr<sf::Drawable> Colored( const KUDA::Rectangle& bounds,
                                                             const sf::Color& color,
                                                             float facingDirection,
                                                             float distance ) const;

        [[nodiscard]] std::unique_ptr<sf::Drawable> Textured( const KUDA::Rectangle& bounds,
                                                              int textureNumber,
                                                              float textureOffset,
                                                              float facingDirection,
                                                              float distance ) const;

        void ApplyShading( sf::Color& base, float facingDirection ) const;

        void ApplyFog( sf::Color& base, float distance ) const;

        void ShadeObject( sf::Transformable* object, float distance) const;
    };
}


#endif //GAME_LIGHTINGANALYZER_H
