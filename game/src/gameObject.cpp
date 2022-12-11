#include "gameObject.h"

bool GameObject::IsAlive() const {
    return isAlive;
}

GameObject::GameObject( float positionX,
                        float positionY,
                        float direction,
                        std::unique_ptr<KUDA::PawnController>&& controller ) : Pawn( positionX,
                                                                                     positionY,
                                                                                     direction,
                                                                                     std::move( controller )) {}
