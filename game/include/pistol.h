#ifndef GAME_PISTOL_H


#define GAME_PISTOL_H

#include "weapon.h"

class Pistol : public Weapon
{
public:
    std::string GetType() override;

    void Use( const Player& player, KUDA::Scene& scene ) override;
};


#endif //GAME_PISTOL_H
