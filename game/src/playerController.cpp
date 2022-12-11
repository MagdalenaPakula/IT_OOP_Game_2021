#include "playerController.h"
#include <cmath>

#define IS_PRESSED( key ) sf::Keyboard::isKeyPressed(sf::Keyboard::key)

void PlayerController::OnUpdate( int deltaTime ) {

    HandleMovement( deltaTime );

    HandleRotation( deltaTime );
}

void PlayerController::HandleRotation( int deltaTime ) {
    auto& player = GetControlledPawn();
    if ( IS_PRESSED( A ))
        SetControlledDirection( player.GetDirection() + rotationSpeed * deltaTime / 1000.f );
    else if ( IS_PRESSED( D ))
        SetControlledDirection( player.GetDirection() - rotationSpeed * deltaTime / 1000.f );

    SetControlledDirection((float) fmod( player.GetDirection(), M_PI * 2 ));
}

void PlayerController::HandleMovement( int deltaTime ) {
    if ( IS_PRESSED( W ) or IS_PRESSED( S )) {
        auto& player = GetControlledPawn();
        const float distance = movementSpeed * deltaTime / 1000.f;

        float newX = player.GetPositionX() + cos( player.GetDirection()) * distance * ( IS_PRESSED( W ) ? 1 : -1 );
        if ( scene.lock()->map->IsWall( newX, player.GetPositionY())) newX = player.GetPositionX();

        float newY = player.GetPositionY() - sin( player.GetDirection()) * distance * ( IS_PRESSED( W ) ? 1 : -1 );
        if ( scene.lock()->map->IsWall( newX, newY )) newY = player.GetPositionY();

        if ( newX > 100.f )
            newX = 100.f;
        if ( newX < 0 )
            newX = 0;

        if ( newY > 100.f )
            newY = 100.f;
        if ( newY < 0 )
            newY = 0;

        SetControlledX( newX );
        SetControlledY( newY );
    }
}

PlayerController::PlayerController( const std::weak_ptr<KUDA::Scene>& scene ) : GameObjectController( scene ) {}
