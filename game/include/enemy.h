#ifndef GAME_ENEMY_H
#define GAME_ENEMY_H

#include "gameObject.h"

class Enemy : public GameObject
{
    int _health;
    int _maxHealth;
public:
    Enemy( float positionX,
           float positionY,
           float direction,
           std::unique_ptr<KUDA::PawnController>&& controller,
           int health );

    void TakeDamage( int amount );

    int GetHealth() const;
};


#endif //GAME_ENEMY_H
