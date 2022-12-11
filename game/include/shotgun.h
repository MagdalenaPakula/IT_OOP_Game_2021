#ifndef GAME_SHOTGUN_H
#define GAME_SHOTGUN_H

#include "weapon.h"

class Shotgun : public Weapon
{
public:
    std::string GetType() override;

    void Use( const Player& player, KUDA::Scene& scene ) override;
};


#endif //GAME_SHOTGUN_H
