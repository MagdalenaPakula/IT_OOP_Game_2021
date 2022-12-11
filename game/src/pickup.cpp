#include "pickup.h"
#include "player.h"

float Pickup::GetRadius() const {
    return radius;
}

Pickup::Pickup( float positionX,
                float positionY,
                float direction,
                std::unique_ptr<KUDA::PawnController>&& controller,
                float radius,
                std::unique_ptr<IPickupAction>&& onPickup ) : GameObject( positionX,
                                                                          positionY,
                                                                          direction,
                                                                          std::move( controller )),
                                                              radius( radius ),
                                                              onPickup( std::move( onPickup )) {}
