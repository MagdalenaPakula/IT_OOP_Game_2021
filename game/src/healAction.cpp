#include "healAction.h"

HealAction::HealAction( int amount ) : _amount( amount ) {}

void HealAction::InvokeOn( Player& player ) {
	player.Heal(_amount);
}
