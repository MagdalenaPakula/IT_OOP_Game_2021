#ifndef GAME_PROJECTILECONTROLLER_H
#define GAME_PROJECTILECONTROLLER_H

#include "pickupController.h"

class ProjectileController : public PickupController
{
public:
    ProjectileController( std::weak_ptr<KUDA::Scene> scene, float movementSpeed );

    void OnUpdate( int deltaTime ) override;

    void PerformMovement( int deltaTime );
};



#endif //GAME_PROJECTILECONTROLLER_H
