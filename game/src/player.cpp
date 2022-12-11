#include "player.h"

Player::Player( float positionX,
                float positionY,
                float direction,
                std::unique_ptr<KUDA::PawnController>&& controller,
                int health ) : GameObject( positionX, positionY, direction, std::move( controller )),
                               _health( health ),
                               _maxHealth( health ) {}

void Player::TakeDamage( int amount ) {
    _health -= amount;
    if ( _health <= 0 ) {
        _health = 0;
        isAlive = false;
    }
}

void Player::Heal( int amount ) {
    if ( !isAlive ) return;

    _health += amount;
    if ( _health > _maxHealth )
        _health = _maxHealth;
}

void Player::AddWeapon( std::unique_ptr<Weapon> weapon ) {
    if ( _weapons.contains( weapon->GetType())) {
        AddAmmo( weapon->GetType(), weapon->GetAmmo());
    } else {
        _weapons[weapon->GetType()] = std::move( weapon );
    }
}

void Player::AddAmmo( const std::string& weaponType, int amount ) {
    if ( _weapons.contains( weaponType )) {
        _weapons[weaponType]->LoadAmmo( amount );
    }
}

int Player::GetHealth() const {
    return _health;
}

std::unique_ptr<sf::Transformable> Player::Get2DSprite() const {
    auto c = std::unique_ptr<sf::RectangleShape>( new sf::RectangleShape( { 5, 10 } ));
    c->setOrigin( 2.5, 5 );
    c->setFillColor( sf::Color::Red );
    return c;
}

std::unique_ptr<sf::Transformable> Player::Get3DSprite( float lookingDirection ) const {
    return {};
}

const std::map<std::string, std::unique_ptr<Weapon>>& Player::GetWeapons() const {
    return _weapons;
}

