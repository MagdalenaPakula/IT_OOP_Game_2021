#ifndef GAME_ACTOR_H
#define GAME_ACTOR_H

#include <memory>
#include <SFML/graphics.hpp>

namespace KUDA
{
    class Actor
    {
    protected:
        float positionX = 0;
        float positionY = 0;
        float direction = 0;
    public:
        explicit Actor( float positionX, float positionY, float direction );

        virtual ~Actor() = default;

        [[nodiscard]] virtual std::unique_ptr<sf::Transformable> Get2DSprite() const = 0;

        [[nodiscard]] virtual std::unique_ptr<sf::Transformable> Get3DSprite( float lookingDirection ) const = 0;

        [[nodiscard]] float GetPositionX() const;

        [[nodiscard]] float GetPositionY() const;

        [[nodiscard]] float GetDirection() const;
    };
}


#endif //GAME_ACTOR_H
