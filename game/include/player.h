#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H
#include <memory>
#include <string>
#include <map>
#include "gameObject.h"
#include "weapon.h"

class Player : public GameObject
{
private:
    int _health;
    const int _maxHealth;
    std::map<std::string, std::unique_ptr<Weapon>> _weapons{};

public:
    Player( float positionX,
            float positionY,
            float direction,
            std::unique_ptr<KUDA::PawnController>&& controller,
            int health );

    Player() = delete;

    void TakeDamage( int amount );

    void Heal( int amount );

    void AddWeapon( std::unique_ptr<Weapon> weapon );

    void AddAmmo( const std::string& weaponType, int amount );

    [[nodiscard]]
    std::unique_ptr<sf::Transformable> Get2DSprite() const override;

    [[nodiscard]]
    std::unique_ptr<sf::Transformable> Get3DSprite( float lookingDirection ) const override;

    [[nodiscard]]
    int GetHealth() const;

    [[nodiscard]]
    const std::map<std::string, std::unique_ptr<Weapon>>& GetWeapons() const;
};


#endif //GAME_PLAYER_H
