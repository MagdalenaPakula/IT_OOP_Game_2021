#ifndef GAME_WEAPON_H
#define GAME_WEAPON_H

#include <string>
#include "KUDA/scene.h"
class Player;

class Weapon
{
private:
    float damage;
    int ammo;
public:
    virtual ~Weapon() = default;

    virtual std::string GetType() = 0;

    float GetDamage() const;

    int GetAmmo() const ;

    void LoadAmmo( int amount );

    virtual void Use(const Player& player, KUDA::Scene& scene) = 0;
};


#endif //GAME_WEAPON_H
