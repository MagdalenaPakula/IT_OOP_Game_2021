#include <cmath>
#include "lightingAnalyzer.h"
#include "wallSpriteFactory.h"

KUDA::LightingAnalyzer::LightingAnalyzer( std::shared_ptr<WallSpriteFactory> spriteFactory ) : spriteFactory(
        std::move(spriteFactory) ) {
}

std::unique_ptr<sf::Drawable> KUDA::LightingAnalyzer::Colored( const KUDA::Rectangle& bounds,
                                                               const sf::Color& color,
                                                               float facingDirection,
                                                               float distance ) const {
    sf::Color base = color;
    ApplyShading( base, facingDirection );
    ApplyFog( base, distance );
    auto rect = spriteFactory->Colored( bounds, base );
    return rect;
}

void KUDA::LightingAnalyzer::ApplyFog( sf::Color& base, float distance ) const {
    auto relativeDistance = distance / 100.f;
    auto dimFactor = 1 / (1 + fogIntensity * pow(relativeDistance,fogExponent) );
    base = sf::Color(base.r * dimFactor, base.g * dimFactor, base.b * dimFactor);
}

std::unique_ptr<sf::Drawable> KUDA::LightingAnalyzer::Textured( const KUDA::Rectangle& bounds,
                                                                int textureNumber,
                                                                float textureOffset,
                                                                float facingDirection,
                                                                float distance ) const {
    if ( spriteFactory == nullptr )
        throw std::runtime_error( "No sprite factory" );
    auto rect = spriteFactory->Textured( bounds, textureNumber, textureOffset );
    sf::Color base = { baseLightLevel, baseLightLevel, baseLightLevel };
    ApplyShading( base, facingDirection );
    rect->setColor( base );
    return rect;
}

void KUDA::LightingAnalyzer::ApplyShading( sf::Color& base, float facingDirection ) const {
    auto lightValue = static_cast<int8_t>(cos(facingDirection - lightingDirection)*shadingIntensity) + baseLightLevel;
    base = sf::Color( base.r + lightValue, base.g + lightValue, base.b + lightValue );
}

void KUDA::LightingAnalyzer::ShadeObject( sf::Transformable* object, float distance ) const {

    if (auto shape = dynamic_cast<sf::Shape*>(object)){
        auto fog = shape->getFillColor();
        ApplyFog( fog, distance);
        shape->setFillColor(fog);
    }
    else if(auto sprite = dynamic_cast<sf::Sprite*>(object)) {
        auto fog = sf::Color::White;
        ApplyFog( fog, distance );
        sprite->setColor( fog );
    }
}
