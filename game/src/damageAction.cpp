#include "damageAction.h"

DamageAction::DamageAction( int amount ) : _amount( amount ) {}

void DamageAction::InvokeOn( Player& player ) {
	player.TakeDamage(_amount);
}
