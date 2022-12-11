#include "pawn.h"

KUDA::Pawn::Pawn( float positionX,
                  float positionY,
                  float direction,
                  std::unique_ptr<PawnController>&& controller ) : Actor( positionX, positionY, direction ),
                                                                 controller( std::move( controller )) {
    this->controller->controlledPawn = this;
}

KUDA::PawnController& KUDA::Pawn::GetController() {
    return *controller;
}