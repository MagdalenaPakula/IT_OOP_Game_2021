#include <cmath>
#include <utility>
#include "projectileController.h"

void ProjectileController::OnUpdate( int deltaTime ) {
    PickupController::OnUpdate( deltaTime );
    PerformMovement( deltaTime );
}

void ProjectileController::PerformMovement( int deltaTime ) {
    const float distance = deltaTime * movementSpeed;
    float newX = GetControlledPawn().GetPositionX() + cos( GetControlledPawn().GetDirection()) * distance;
    float newY = GetControlledPawn().GetPositionY() - sin( GetControlledPawn().GetDirection()) * distance;

    if ( newX > 100.f or newX < 0 or newY > 100.f or newY < 0 or scene.lock()->map->IsWall(newX,newY)){
        DestroyObject();
        return;
    }
    SetControlledX( newX );
    SetControlledY( newY );
}

ProjectileController::ProjectileController( std::weak_ptr<KUDA::Scene> scene, float movementSpeed ) : PickupController(
        std::move( scene )) {
    this->movementSpeed = movementSpeed;
}
