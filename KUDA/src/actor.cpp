#include "actor.h"

KUDA::Actor::Actor( float positionX, float positionY, float direction ) : positionX( positionX ),
                                                                    positionY( positionY ),
                                                                    direction( direction ) {}

float KUDA::Actor::GetPositionX() const {
    return positionX;
}

float KUDA::Actor::GetPositionY() const {
    return positionY;
}

float KUDA::Actor::GetDirection() const {
    return direction;
}