#include "pickupController.h"

bool PickupController::IsColliding() {
    return scene.lock()->camera->DistanceTo( GetControlledPawn()) < dynamic_cast<Pickup&>(GetControlledPawn()).GetRadius();
}

void PickupController::OnUpdate( int deltaTime ) {
    auto& pickup = dynamic_cast<Pickup&>(GetControlledPawn());
    if ( IsColliding()) {
        pickup.onPickup->InvokeOn( dynamic_cast<Player&>(scene.lock()->camera->GetControlledPawn()));
        DestroyObject();
    }
    else if ( scene.lock()->map->IsWall( pickup.GetPositionX(), pickup.GetPositionY())) {
        DestroyObject();
    }
}

PickupController::PickupController( std::weak_ptr<KUDA::Scene> scene ) : GameObjectController( scene ) {}

void PickupController::DestroyObject() {
    dynamic_cast<Pickup&>(GetControlledPawn()).isAlive = false;
}
