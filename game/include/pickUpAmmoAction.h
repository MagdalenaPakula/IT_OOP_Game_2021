#ifndef GAME_PICKUPAMMOACTION_H
#define GAME_PICKUPAMMOACTION_H

#include "IPickupAction.h"

class PickUpAmmoAction : public IPickupAction
{
private:
    std::string _weaponClass;
    int _amount;
public:
    explicit PickUpAmmoAction( std::string weaponClass, int amount );

    void InvokeOn( Player& player ) override;
};



#endif //GAME_PICKUPAMMOACTION_H
