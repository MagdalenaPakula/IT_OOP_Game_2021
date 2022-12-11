#ifndef GAME_PICKUPWEAPONACTION_H
#define GAME_PICKUPWEAPONACTION_H

#include "IPickupAction.h"
#include "weapon.h"

class PickUpWeaponAction : public IPickupAction
{
private:
    std::unique_ptr<Weapon> _weapon;
public:
    explicit PickUpWeaponAction( std::unique_ptr<Weapon> weapon );

    void InvokeOn( Player& player ) override;
};


#endif //GAME_PICKUPWEAPONACTION_H
