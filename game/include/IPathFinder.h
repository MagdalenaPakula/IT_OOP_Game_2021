#ifndef GAME_IPATHFINDER_H
#define GAME_IPATHFINDER_H

#include "KUDA.h"

class IPathFinder {
    virtual float GetDirection(const KUDA::IMap& map, const KUDA::Actor& source, const KUDA::Actor& destination) = 0;
};

#endif //GAME_IPATHFINDER_H
