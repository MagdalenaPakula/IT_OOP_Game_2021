#include "enemy.h"

void Enemy::TakeDamage( int amount ) {
    _health -= amount;
    if ( _health <= 0 ) {
        _health = 0;
        isAlive = false;
    }
    //TO DO
    //what is a type??
}

Enemy::Enemy( float positionX,
              float positionY,
              float direction,
              std::unique_ptr<KUDA::PawnController>&& controller,
              int health ) : GameObject( positionX, positionY, direction, std::move( controller )),
                             _health( health ),
                             _maxHealth( health ) {}

int Enemy::GetHealth() const {
    return _health;
}
