#ifndef GAME_PICKUPCONTROLLER_H
#define GAME_PICKUPCONTROLLER_H

#include "gameObjectController.h"
#include "pickup.h"

class PickupController : public GameObjectController
{
private:
    bool IsColliding();

protected:
    void DestroyObject();

public:
    explicit PickupController( std::weak_ptr<KUDA::Scene> scene );

    void OnUpdate( int deltaTime ) override;
};


#endif //GAME_PICKUPCONTROLLER_H
