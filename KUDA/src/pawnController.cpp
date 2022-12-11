#include "pawnController.h"
#include "pawn.h"

KUDA::Pawn& KUDA::PawnController::GetControlledPawn() {
    if ( controlledPawn == nullptr )
        throw std::runtime_error( "Controller has no pawn" );
    return *controlledPawn;
}

void KUDA::PawnController::SetControlledX( float x ) {
    if ( controlledPawn == nullptr )
        throw std::runtime_error( "Controller has no pawn" );
    controlledPawn->positionX = x;
}

void KUDA::PawnController::SetControlledY( float y ) {
    if ( controlledPawn == nullptr )
        throw std::runtime_error( "Controller has no pawn" );
    controlledPawn->positionY = y;
}

void KUDA::PawnController::SetControlledDirection( float direction ) {
    if ( controlledPawn == nullptr )
        throw std::runtime_error( "Controller has no pawn" );
    controlledPawn->direction = direction;
}
