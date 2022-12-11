#include "pickUpAmmoAction.h"

#include <utility>

PickUpAmmoAction::PickUpAmmoAction( std::string weaponClass, int amount ) : _weaponClass( std::move( weaponClass )),
                                                                            _amount( amount ) {}

void PickUpAmmoAction::InvokeOn( Player& player ) {
    player.AddAmmo( _weaponClass, _amount );
}
