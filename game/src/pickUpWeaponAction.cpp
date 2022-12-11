#include "pickUpWeaponAction.h"

void PickUpWeaponAction::InvokeOn( Player& player ) {
    player.AddWeapon(std::move(_weapon));
}

PickUpWeaponAction::PickUpWeaponAction( std::unique_ptr<Weapon> weapon ) : _weapon( std::move(weapon) ) {}
