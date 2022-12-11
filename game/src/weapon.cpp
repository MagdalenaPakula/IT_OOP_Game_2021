#include "weapon.h"

float Weapon::GetDamage() const {
	return damage;
}

int Weapon::GetAmmo() const {
	return ammo;
}

void Weapon::LoadAmmo( int amount ) {
    ammo += amount;
}
