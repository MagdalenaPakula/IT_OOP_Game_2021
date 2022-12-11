#ifndef GAME_PICKUP_H
#define GAME_PICKUP_H

#include "gameObject.h"
#include "IPickupAction.h"

class Pickup : public GameObject
{
    friend class PickupController;

private:
    float radius;
    std::unique_ptr<IPickupAction> onPickup;

public:
    Pickup( float positionX,
            float positionY,
            float direction,
            std::unique_ptr<KUDA::PawnController>&& controller,
            float radius,
            std::unique_ptr<IPickupAction>&& onPickup );

    float GetRadius() const;
};


#endif //GAME_PICKUP_H
